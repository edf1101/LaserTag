/*
 * Created by Ed Fillingham on 09/04/2024.
*/

#include "Firing.h"
#include "../LaserTag.h"

Firing::Firing(LaserTag *_mySystem) {
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
#if DEBUG
    Serial.println("IR Received");
#endif
    if (infraredTransciever.crcValid)
    {
#if DEBUG
      Serial.println("CRC correct");
#endif

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

  // Deal with gun reloading object
  // May not actually be reloading but that's dealt with in the gun object
  mySystem->getPlayer()->getGun()->reloadLoop();

}

void Firing::OnHit() {
  // This gets called when the gun has been hit by an IR signal

  Player *player = mySystem->getPlayer();

  // Get the data recieved
  int rxUnitnum = infraredTransciever.irPacketIn.unitnum;
  int rxWeapon = infraredTransciever.irPacketIn.weapon;

#if DEBUG
  Serial.println("Rx Hit signal");
  Serial.print("Hit! Shot by: ");
  Serial.print(rxUnitnum);
  Serial.print(" with weapon: ");
  Serial.println(rxWeapon);
#endif

  if (mySystem->canTakeDamage(rxUnitnum)) {
#if DEBUG
    Serial.println("Valid hit");
#endif
    player->takeDamage(rxWeapon); // Deal damage to the player based on the weapon that hit them
  }
}

void Firing::OnCommand() {
  // This gets called when the gun has received a control packet

  // Get the unitnum and weapon from the packet and combine them into a command
  int unitnum = infraredTransciever.irPacketIn.unitnum;
  int weapon = infraredTransciever.irPacketIn.weapon;
  int command = weapon << 7 | unitnum;
#if DEBUG
  Serial.print("Control packet received: ");
  Serial.println(command);
#endif

  //TODO pass this on to a callback func somewhere
}

void Firing::sendCommand(uint16_t command) {
  /* This function sends a command signal to other guns
   * eg. respawn, new game etc.
   * This is a higher level function that calls the lower level IR function
   */

  // We have 11 bits for commands (plenty) make sure command id is within that range
  if (command > 2048) {
    Serial.println("Command too large");
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
  Player *player = mySystem->getPlayer();
  Weapons::Gun *myGun = player->getGun();
  if (!myGun->tryFire()) { // If the gun can't fire then skip past this
    return;
  }

  digitalWrite(MUZZLE_LED,LOW); // Turn it off in case was still on from last shot (so doesn't interfere with IR signal)
  digitalWrite(VIBRATE_PIN, LOW); // Same as above
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
  if(allowVibrations){
    digitalWrite(VIBRATE_PIN, HIGH);
    vibrating = true;
    lastVibrate = millis();
  }

  mySystem->updateHUD();

}

void Firing::OnTriggerUp() {
  // This function gets called when the trigger is pressed
  Player *player = mySystem->getPlayer();
  Weapons::Gun *myGun = player->getGun();
  myGun->resetBurstCount();
}

void Firing::OnMagazineButtonDown() {
  // This function gets called when the magazine button is pressed
  Player *player = mySystem->getPlayer();
  Weapons::Gun *myGun = player->getGun();
  myGun->reloadAddBullet();
}