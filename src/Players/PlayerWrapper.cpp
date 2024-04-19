/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the Players's data and stats.
*/

#include <utility>
#include "PlayerWrapper.h"
#include "../LaserTag.h"

// constructor for player
void PlayerWrapper::init(LaserTag *_mySystem, int _unitnum, int _team) {
  player.unitnum = _unitnum;
  player.team = _team;
  player.name = "Player" + std::to_string(_unitnum);
  player.revives = START_LIVES;
  player.health = 100;
  player.kills = 0;
  player.carryingFlag = false;

  mySystem = _mySystem;

  gun.setHUDFunction(std::bind(&LaserTag::updateHUD, mySystem)); // update the HUD function

  player.gunIndex = getGun()->getIndex();
}

// getter and setter for unitnum
int PlayerWrapper::getUnitnum() const {
  return player.unitnum;
}

void PlayerWrapper::setUnitnum(int _unitnum) {
  player.unitnum = _unitnum;
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
}

// getter & setter for revives
int PlayerWrapper::getRevives() const {
  return player.revives;
}

void PlayerWrapper::setRevives(int _revives) {
  player.revives = _revives;
}

// getter & setter for health
int PlayerWrapper::getHealth() const {
  return player.health;
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

bool PlayerWrapper::canFire() {
  if (player.health <= 0) return false; // if the player is dead they can't fire
  if (player.revives < 0) return false; // if the player has no revives left they can't fire

  return true; // at the end if it passed all the checks then the player can fire
}

void PlayerWrapper::takeDamage(int _gunIndex) {
  // deal damage to the player

  int gunDamage = WeaponsManager::getGun(_gunIndex).getDamage(); // get the gun that shot the player
#if DEBUG
  Serial.print("Players took damage: ");
  Serial.println(gunDamage);
#endif
  player.health -= gunDamage;
  if (player.health <= 0) {
    player.health = 0;
    mySystem->getGamemode()->onPlayerDeath();
    if (player.revives > 0) {
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
#if DEBUG
    Serial.println("Players respawned");
#endif
    player.health = 100;
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

  return true; // passed all checks so return true
}


void PlayerWrapper::swapGun(std::string gunName) {
  // Fairly swap guns for the player

  // calculate the percentage of mags remaining
  int currentMags = gun.getMagsRemaining();
  int startMags = gun.getInitialMags();
  float magsRatio = (float) currentMags / (float) startMags;

  // set the new gun so that it has the same percentage of mags remaining
  Weapons::Gun newGun = WeaponsManager::getGun(gunName);
  int newGunMagsRemaining = ((int) ((float) magsRatio * newGun.getInitialMags()));
  int newGunAmmoRemaining = (newGunMagsRemaining > 0) ? newGun.getInitialAmmo() : 0;
  newGun.setAmmoAndMags(newGunAmmoRemaining, newGunMagsRemaining);

  gun = newGun; // assign the new gun to the player

  gun.setHUDFunction(std::bind(&LaserTag::updateHUD, mySystem)); // update the HUD function

}
