/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the Players's data and stats.
*/

#include <utility>
#include "PlayerWrapper.h"
#include "../LaserTag.h"

// constructor for player
void PlayerWrapper::init(int _team) {
  player.unitnum = random(1, 127);
  player.team = _team;
  player.name = "Gun" + std::to_string(player.unitnum);
  player.revives = 0;
  player.health = 100;
  player.kills = 0;
  player.carryingFlag = false;

  gun.setHUDFunction(std::bind(&LaserTag::updateHUD, mySystem)); // update the HUD function

  player.gunIndex = getGun()->getIndex();
}

// getter and setter for unitnum
int PlayerWrapper::getUnitnum() const {
  return player.unitnum;
}

void PlayerWrapper::setUnitnum(int _unitnum) {
  player.unitnum = _unitnum;

  if (!customName) { // If we haven't set a custom name then update the name to match the unitnum
    player.name = "Player" + std::to_string(player.unitnum);
  }
}

// getter and setter for team
int PlayerWrapper::getTeam() const {
  return player.team;
}

void PlayerWrapper::setTeam(int _team) {
  player.team = _team;
}

// getter and setter for name
std::string PlayerWrapper::getName() const {
  return player.name;
}

void PlayerWrapper::setName(std::string _name) {
  // move the string to the name (moving instead of assigning saves memory)
  player.name = std::move(_name);
  customName = true;
}

// getter & setter for revives
int PlayerWrapper::getRevives() const {

  if (currentInfiniteLivesState == INFINITE_LIVES || currentInfiniteLivesState == INVINCIBLE_LIVES)
    return -1; // if the player has infinite or invincible lives then return -1

  return player.revives; // if normal revives then just return them
}

void PlayerWrapper::setRevives(int _revives) {
  player.revives = _revives;
}

// getter & setter for health
int PlayerWrapper::getHealth() const {

  if (currentInfiniteLivesState == INVINCIBLE_LIVES)
    return -1; // if the player is invincible then return -1

  return player.health; // if normal health then just return it
}

void PlayerWrapper::setHealth(int _health) {
  player.health = _health;
}

// getter & setter for kills
int PlayerWrapper::getKills() const {
  return player.kills;
}

void PlayerWrapper::setKills(int _kills) {
  player.kills = _kills;
}

// getter & setter for carryingFlag
bool PlayerWrapper::getCarryingFlag() const {
  return player.carryingFlag;
}

void PlayerWrapper::setCarryingFlag(bool _carryingFlag) {
  player.carryingFlag = _carryingFlag;
}

// getter & setter for gun
Weapons::Gun *PlayerWrapper::getGun() {
  return &gun;
}

void PlayerWrapper::swapGun(std::string gunName) {
  // Fairly swap guns for the player

  // Check new gun is part of the current gun group
  vector<Weapons::Gun> allActiveGuns = WeaponsManager::getAllGuns();
  bool gunFound = false;
  for (auto &_gun: allActiveGuns) {
    if (_gun.getName() == gunName) {
      gunFound = true;
      break;
    }
  }
  if (gunFound == false) {
    return; // if the gun isn't found then return
  }

  // calculate the percentage of mags remaining
  int currentMags = gun.getMagsRemaining();
  int startMags = gun.getInitialMags();

  if (currentMags == -1) currentMags = startMags; // if infinite mags then set to start mags
  float magsRatio = (float) currentMags / (float) startMags;

  // set the new gun so that it has the same percentage of mags remaining
  Weapons::Gun newGun = WeaponsManager::getGun(gunName);
  int newGunMagsRemaining = ((int) ((float) magsRatio * newGun.getInitialMags()));
  int newGunAmmoRemaining = (newGunMagsRemaining > 0) ? newGun.getInitialAmmo() : 0;
  newGun.setAmmoAndMags(newGunAmmoRemaining, newGunMagsRemaining);

  gun = newGun; // assign the new gun to the player

  gun.setHUDFunction(std::bind(&LaserTag::updateHUD, mySystem)); // update the HUD function

}

void PlayerWrapper::resetGun() {
  // reset a gun so it has full ammo and mags, no longer supressed, inf ammo etc

  Weapons::Gun currentGun = gun;
  std::string currentName = gun.getName();

  gun = WeaponsManager::getGun(currentName); // reset the gun to the same gun (just new instance)

}

bool PlayerWrapper::canFire() {
  if (player.health <= 0) return false; // if the player is dead they can't fire
  if (player.revives < 0) return false; // if the player has no revives left they can't fire

  return true; // at the end if it passed all the checks then the player can fire
}

void PlayerWrapper::takeDamage(int _gunIndex) {
  // deal damage to the player

  int gunDamage = WeaponsManager::getGun(_gunIndex).getDamage(); // get the gun that shot the player
  Logger::log(Logger::LogLevel::INFO, "I took " + std::to_string(gunDamage) + " damage");
  player.health -= gunDamage;
  if (player.health <= 0) {
    Logger::log(Logger::LogLevel::DETAIL, "I died");
    player.health = 0;
    mySystem->getGamemode()->onPlayerDeath();
    if (player.revives > 0) {
      Logger::log(Logger::LogLevel::DETAIL, "Starting respawn");
      respawn();
    }
  }
  mySystem->updateHUD(); // update the HUD that we took damage
}

void PlayerWrapper::respawn() {
  respawning = true;
  respawnStartTime = millis();
}

float PlayerWrapper::getRespawnStatus() {
  // return the progress of the respawn: 0 if not respawning, 0-1 if respawning
  if (!respawning) {
    return 0;
  } else {
    return (float) (millis() - respawnStartTime) / RESPAWN_TIME;
  }
}

void PlayerWrapper::loop() {
  // This function will be called every loop

  // Deal with respawn logic
  if (respawning && (millis() - respawnStartTime > RESPAWN_TIME)) {
    Logger::log(Logger::LogLevel::INFO, "Respawn complete");

    player.health = 100;
    if (currentInfiniteLivesState == NORMAL_LIVES) // Normal lives is the only state that uses up a revive
      player.revives--;
    respawning = false;
  }
}

bool PlayerWrapper::canTakeDamage(int shooterUnitnum) {
  // Returns true if the player can take damage

  if (respawning) return false; // if the player is respawning they can't take damage

  if (shooterUnitnum == player.unitnum) return false; // if the shooter is the same as the player they can't take damage

  if (player.revives == 0 && player.health <= 0)
    return false; // if the player has no revives left and is dead they can't take damage

  if (currentInfiniteLivesState == INVINCIBLE_LIVES) return false; // if the player is invincible they can't take damage

  return true; // passed all checks so return true
}

void PlayerWrapper::setPlayerToTemplate(Player *target, Player templatePlayer) {
  // Update the target player to match the template player's gameplay details
  // so DON'T modify the target player's name, team, or unitnum.

  target->revives = templatePlayer.revives;
  target->health = templatePlayer.health;
  target->kills = templatePlayer.kills;
  target->carryingFlag = templatePlayer.carryingFlag;

}

void PlayerWrapper::setPlayerToTemplate(Player templatePlayer) {
  // the non-static version of this function that sets the player to the template player

  setPlayerToTemplate(&player, templatePlayer);

  resetGun();
  gun.setHUDFunction(std::bind(&LaserTag::updateHUD, mySystem)); // update the HUD function
  respawning = false; // reset the respawn status
  respawnStartTime = 0;

}

void PlayerWrapper::setInfiniteLivesState(PlayerWrapper::InfiniteLivesState state) {
  // Set the player's infinite lives state

  currentInfiniteLivesState = state;
}

PlayerWrapper::InfiniteLivesState PlayerWrapper::getInfiniteLivesState() {
  // Return the player's infinite lives state

  return currentInfiniteLivesState;
}
