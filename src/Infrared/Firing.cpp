/*
 * Created by Ed Fillingham on 09/04/2024.
*/

#include "Firing.h"
#include "../LaserTag.h"

Firing::Firing(LaserTag *_mySystem) {
  // constructor to link the whole laserTag system to this firing class
  // This is important, so it can access sounds, player data, etc.
  mySystem = _mySystem;

  // set up low level IR transceiver
  infraredTransciever.init(IR_RECEIVER, IR_TRANSMITTER);
}

void Firing::FiringLoop() {
  infraredTransciever.receiveIR();
  //Serial.println(canRx);
  if (infraredTransciever.infraredReceived) {  // canRx bit used to be up here if any weird issues try moving back up here


    if (infraredTransciever.crcValid)  // if valid reception and we're running ... also make you invincible if you are in an admin menu, ie you cant run commands
    {

      int irControl = infraredTransciever.irPacketIn.control;
      int irUnitnum = infraredTransciever.irPacketIn.unitnum;
      int irWeapon = infraredTransciever.irPacketIn.weapon;
      Serial.println("rxIR");
      if (irControl == 0) {  //recieved shot control signal
        OnHit();
      }
      if (irControl == 1) {
        OnCommand();

      }
    }
    infraredTransciever.infraredReceived = 0;
  }

}

void Firing::OnHit() {
  // This gets called when the gun has been hit by an IR signal

  // TODO make it so own unitnum can't be hit once player class done
  // TODO have callback func if required by gamemode (gamemode should have a special callback on top of this)
  //  usual gamemodes won't need as this will handle lives remove and if teams / friendly fire etc.

  // Get the data
  int unitnum = infraredTransciever.irPacketIn.unitnum;
  int weapon = infraredTransciever.irPacketIn.weapon;

  Serial.print("Hit! Shot by: ");
  Serial.print(unitnum);
  Serial.print(" with weapon: ");
  Serial.println(weapon);

}

void Firing::OnCommand() {
  // This gets called when the gun has received a control packet

  // Get the unitnum and weapon from the packet and combine them into a command
  int unitnum = infraredTransciever.irPacketIn.unitnum;
  int weapon = infraredTransciever.irPacketIn.weapon;
  int command = weapon << 7 | unitnum;

  Serial.print("Control packet received: ");
  Serial.println(command);

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

  // Will fake these for now
  //TODO implement real weapon and unitnum once player and weapon classes are implemented
  int weapon = 1; // weapon number  (MAX 2^4 = 16)
  int unitnum = 1; // unit number (MAX 2^7 = 128)

  infraredTransciever.sendIR(0, (uint8_t) unitnum, (uint8_t) weapon);
}