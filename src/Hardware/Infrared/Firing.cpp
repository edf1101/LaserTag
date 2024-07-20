/*
 * Created by Ed Fillingham on 09/04/2024.
*/

#include "Firing.h"
#include "../../LaserTag.h"
#include "../../Commands/CommandManager.h"

void Firing::init(LaserTag *_mySystem) {
  // This function is called once at the start of the game
  // It sets up the firing system
  // constructor to link the whole laserTag system to this firing class
  // This is important, so it can access sounds, player data, etc.

  mySystem = _mySystem;

  // set up buttons
  gameButtons = mySystem->getButtons();
  gameButtons->triggerButton.SetReleasedCallback(std::bind(&Firing::OnTriggerUp, this));
  gameButtons->magazineButton.SetPressedCallback(std::bind(&Firing::OnMagazineButtonDown, this));

  // set up low level IR transceiver
  infraredTransciever.init(IR_RECEIVER, IR_TRANSMITTER);

  // set up muzzle flash LED
  pinMode(MUZZLE_LED, OUTPUT);
  pinMode(VIBRATE_PIN, OUTPUT);
}

void Firing::FiringLoop() {
  // This gets called every call of the main loop and deals with things related to firing and IR signals

  infraredTransciever.receiveIR(); // check for IR signals in
  if (infraredTransciever.infraredReceived) {

    Logger::log(Logger::LogLevel::DETAIL, "IR Received");
    if (infraredTransciever.crcValid) {

      Logger::log(Logger::LogLevel::DETAIL, "IR CRC correct");


      int irControl = infraredTransciever.irPacketIn.control;

      if (irControl == 0) {  // received shot control signal
        OnHit();
      }
      if (irControl == 1) {
        OnCommand();
      }
    }
    infraredTransciever.infraredReceived = 0;
  }

  if (gameButtons->triggerButton.isPressed() && mySystem->canFire()) {
    // Check if able to fire and trigger is pressed
    Fire();
  }

  // Deal with muzzle flash
  if (muzzleFlash && millis() - lastMuzzleFlash > MUZZLE_FLASH_TIME) {
    muzzleFlash = false;
    digitalWrite(MUZZLE_LED, LOW);
  }
  if (vibrating && millis() - lastVibrate > VIBRATE_TIME) {
    vibrating = false;
    digitalWrite(VIBRATE_PIN, LOW);
  }

  if (millis() - lastTurnOffNeopixels > MUZZLE_FLASH_TIME) {
    mySystem->getLEDManager()->setLEDState(true);
  }

  // Deal with gun reloading object
  // May not actually be reloading but that's dealt with in the gun object
  mySystem->getPlayer()->getGun()->reloadLoop();

}

void Firing::OnHit() {
  // This gets called when the gun has been hit by an IR signal

  PlayerWrapper *player = mySystem->getPlayer();

  // Get the data recieved
  int rxUnitnum = infraredTransciever.irPacketIn.unitnum;
  int rxWeapon = infraredTransciever.irPacketIn.weapon;


  Logger::log(Logger::LogLevel::DETAIL,
              "Hit! Shot by: " + std::to_string(rxUnitnum) + " with weapon: " + std::to_string(rxWeapon));

  if (mySystem->canTakeDamage(rxUnitnum)) {

    Logger::log(Logger::LogLevel::DETAIL, "Valid hit");
    player->takeDamage(rxWeapon); // Deal damage to the player based on the weapon that hit them

    // send a hit signal back. if the player is respawning, set killConfirm flag to true.
    LaserTag::getNetworkManager()->sendHitConfirmation(rxUnitnum, player->getUnitnum(), player->getHealth() == 0);
  }
}

void Firing::OnCommand() {
  // This gets called when the gun has received a control packet

  // Get the unitnum and weapon from the packet and combine them into a command
  int unitnum = infraredTransciever.irPacketIn.unitnum;
  int weapon = infraredTransciever.irPacketIn.weapon;
  int command = weapon << 7 | unitnum;

  Logger::log(Logger::LogLevel::DETAIL, "Control packet received: " + std::to_string(command));

  // pass onto the command manager
  Commands::Command *rxCommand = Commands::Command::getCommandByIndex(command);
  LaserTag::getCommandManager()->processCommand(rxCommand);
}

void Firing::sendCommand(uint16_t command) {
  /* This function sends a command signal to other guns
   * eg. respawn, new game etc.
   * This is a higher level function that calls the lower level IR function
   */

  // We have 11 bits for commands (plenty) make sure command id is within that range
  if (command > 2048) {
    Logger::log(Logger::LogLevel::ERROR,"Command ID too large: " + std::to_string(command));

    return;
  }

  // The irPacketStruct expects weapon and unitnum as fields not command,
  // We will combine our command into these fields using bitwise logic.
  int weapon = (int) command >> 7;
  int unitnum = (int) command & 0b00001111111;

  // Send the packet over IR
  infraredTransciever.sendIR(1, (uint8_t) unitnum, (uint8_t) weapon);
}

void Firing::Fire() {
  // This function sends a shot signal to other guns

  // Get the current gun object and check it can fire
  PlayerWrapper *player = LaserTag::getPlayer();
  Weapons::Gun *myGun = player->getGun();
  if (!myGun->tryFire()) { // If the gun can't fire then skip past this
    return;
  }

  digitalWrite(MUZZLE_LED,
               LOW); // Turn it off in case was still on from last shot (so doesn't interfere with IR signal)
  digitalWrite(VIBRATE_PIN, LOW); // Same as above
  LaserTag::getLEDManager()->setLEDState(false); // same as above
  lastTurnOffNeopixels = millis();

  // Send the actual data over IR
  int weapon = myGun->getIndex(); // weapon number  (MAX 2^4 = 16)
  int unitnum = player->getUnitnum(); // unit number (MAX 2^7 = 128)
  infraredTransciever.sendIR(0, (uint8_t) unitnum, (uint8_t) weapon);

  // Do muzzle flash / sound effect if not suppressed
  if (!myGun->getSuppressed()) {
    muzzleFlash = true;
    lastMuzzleFlash = millis();
    digitalWrite(MUZZLE_LED, HIGH);
    mySystem->getSoundPlayer()->playSound(myGun->getSound());
  }
  // Deal with vibrations
  if (allowVibrations) {
    digitalWrite(VIBRATE_PIN, HIGH);
    vibrating = true;
    lastVibrate = millis();
  }

  mySystem->updateHUD();

}

void Firing::OnTriggerUp() {
  // This function gets called when the trigger is pressed
  PlayerWrapper *player = mySystem->getPlayer();
  Weapons::Gun *myGun = player->getGun();
  myGun->resetBurstCount();
}

void Firing::OnMagazineButtonDown() {
  // This function gets called when the magazine button is pressed
  PlayerWrapper *player = mySystem->getPlayer();
  Weapons::Gun *myGun = player->getGun();
  myGun->reloadAddBullet();
}