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
  displayHud = mySystem->getHudDisplay();
}

void Gamemode::initialisePlayer() {
  // This function sets up the player so it's ready to play when the game starts
  Player *player = mySystem->getPlayer();

  player->setHealth(100);
  player->setRevives(playerStartingRevives);
  player->setKills(0);
  player->setCarryingFlag(false);

  // If the player is on a team, set the team
    if (teamBased) {
        player->setTeam(0);
    }
    else{
      player->setTeam(-1);
    }
}

void Gamemode::startGame() {
  started = true;
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



std::string Gamemode::getName() {
  return name;
}

void Gamemode::drawHUD() {
  displayHud->getDisplay()->clearDisplay();
  displayHud->drawRevives();
  displayHud->getDisplay()->display();
}
