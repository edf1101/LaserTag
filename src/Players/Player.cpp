/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the Players's data and stats.
*/

#include <utility>
#include "Player.h"
#include "../LaserTag.h"

// constructor for player
void Player::init(LaserTag *_mySystem, int _unitnum, int _team) {
  unitnum = _unitnum;
  team = _team;
  name = "Players" + std::to_string(unitnum);
  mySystem = _mySystem;

  setGun(DEFAULT_GUN);
}

// getter and setter for unitnum
int Player::getUnitnum() const {
  return unitnum;
}

void Player::setUnitnum(int _unitnum) {
  unitnum = _unitnum;
}

// getter and setter for team
int Player::getTeam() const {
  return team;
}

void Player::setTeam(int _team) {
  team = _team;
}

// getter and setter for name
std::string Player::getName() const {
  return name;
}

void Player::setName(std::string _name) {
  // move the string to the name (moving instead of assigning saves memory)
  name = std::move(_name);
}

// getter & setter for revives
int Player::getRevives() const {
  return revives;
}

void Player::setRevives(int _revives) {
  revives = _revives;
}

// getter & setter for health
int Player::getHealth() const {
  return health;
}

void Player::setHealth(int _health) {
  health = _health;
}

// getter & setter for kills
int Player::getKills() const {
  return kills;
}

void Player::setKills(int _kills) {
  kills = _kills;
}

// getter & setter for carryingFlag
bool Player::getCarryingFlag() const {
  return carryingFlag;
}

void Player::setCarryingFlag(bool _carryingFlag) {
  carryingFlag = _carryingFlag;
}

// getter & setter for gun
Weapons::Gun *Player::getGun() {
  return gun;
}

bool Player::canFire() {
  if (health <= 0) return false; // if the player is dead they can't fire
  if (revives < 0) return false; // if the player has no revives left they can't fire

  return true; // at the end if it passed all the checks then the player can fire
}

void Player::takeDamage(int _gunIndex) {
  // deal damage to the player

  int gunDamage = myGuns.getGun(_gunIndex)->getDamage(); // get the gun that shot the player
#if DEBUG
  Serial.print("Players took damage: ");
  Serial.println(gunDamage);
#endif
  health -= gunDamage;
  if (health <= 0) {
    health = 0;
    mySystem->getGamemode()->onPlayerDeath();
    if (revives > 0) {
      respawn();
    }
  }
  mySystem->updateHUD(); // update the HUD that we took damage
}

void Player::respawn() {
  respawning = true;
  respawnStartTime = millis();
}

float Player::getRespawnStatus() {
  // return the progress of the respawn: 0 if not respawning, 0-1 if respawning
  if (!respawning) {
    return 0;
  } else {
    return (float) (millis() - respawnStartTime) / RESPAWN_TIME;
  }
}

void Player::loop() {
  // This function will be called every loop

  // Deal with respawn logic
  if (respawning && (millis() - respawnStartTime > RESPAWN_TIME)) {
#if DEBUG
    Serial.println("Players respawned");
#endif
    health = 100;
    revives--;
    respawning = false;
  }
}

bool Player::canTakeDamage(int shooterUnitnum) {
  // Returns true if the player can take damage

  if (respawning) return false; // if the player is respawning they can't take damage

  if (shooterUnitnum == unitnum) return false; // if the shooter is the same as the player they can't take damage

  if (revives == 0 && health <= 0) return false; // if the player has no revives left and is dead they can't take damage

  return true; // passed all checks so return true
}

void Player::setGun(std::string gunName) {
  gun = myGuns.getGun(gunName);
  gun->setHUDFunction(std::bind(&LaserTag::updateHUD, mySystem));
}
