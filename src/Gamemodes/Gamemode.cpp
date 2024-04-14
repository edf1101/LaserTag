/*
 * Created by Ed Fillingham on 12/04/2024.
 *
 * This class represents a basic gamemode in the Laser Tag system.
 * Other more complex gamemodes will inherit from this class and add their own functionality.
*/

#include "Gamemode.h"
#include "../LaserTag.h"

Gamemode::Gamemode(LaserTag *_mySystem) {
  mySystem = _mySystem;
  myPlayer = mySystem->getPlayer();
  displayHud = mySystem->getHudDisplay();
  displayHud->setInfoStateCounts(2); // 2 states: display name, display gun

  // Initialise the widgets after the constructor has got pointers for display player, etc
}

void Gamemode::initialisePlayer() {
  // This function sets up the player so it's ready to play when the game starts

  myPlayer->setHealth(100);
  myPlayer->setRevives(playerStartingRevives);
  myPlayer->setKills(0);
  myPlayer->setCarryingFlag(false);

  // If the player is on a team, set the team
  if (teamBased) {
    myPlayer->setTeam(0);
  } else {
    myPlayer->setTeam(-1);
  }
}

bool Gamemode::canFire() {
// This checks if the gun can fire according to gamemode rules

  if (!started) return false; // If the game hasn't started, return false

  return true; // If passed all conditions, return true
}

void Gamemode::onPlayerDeath() {

}

void Gamemode::onPickupRespawn() {

}

void Gamemode::onPickupFlag() {

}

void Gamemode::onDropFlag() {

}

void Gamemode::drawHUD() {
}


std::string Gamemode::getName() {
  return name;
}


void Gamemode::loop() {
  // This function is called each time the main loop is called

  // update the HUD every so often
    if (millis() - lastHudAutoUpdate > HUD_UPDATE_INTERVAL) {
        lastHudAutoUpdate = millis();
        drawHUD();
    }
}

void Gamemode::setGamePauseState(bool paused) {
  this->started = !paused;
}

bool Gamemode::canTakeDamage(int shooterUnitnum) {

  if (!started) return false; // If the game hasn't started, return false

  // TODO have some logic here to check teams

  return true; // If passed all conditions, return true
}
