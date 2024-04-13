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

  revivesWidget.init(displayHud, std::bind(&Player::getRevives, myPlayer));
  healthWidget.init(displayHud, std::bind(&Player::getHealth, myPlayer));
  ammoWidget.init(displayHud, std::bind(&Weapons::Gun::getAmmoRemaining, myPlayer->getGun()));
  magsWidget.init(displayHud, std::bind(&Weapons::Gun::getMagsRemaining, myPlayer->getGun()));
  infoWidget.init(displayHud);

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
  // This function is called to draw the HUD for the gamemode

  infoWidget.setTexts("Name", myPlayer->getName());

  revivesWidget.draw();
  healthWidget.draw();
  ammoWidget.draw();
  magsWidget.draw();
  infoWidget.draw();

  displayHud->getDisplay()->display();
}

void Gamemode::loop() {
  // This function is called each time the main loop is called

}
