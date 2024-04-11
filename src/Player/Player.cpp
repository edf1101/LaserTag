/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the Player's data and stats.
*/

#include "Player.h"

#include <utility>

// constructor for player
void Player::init(int _unitnum, int _team) {
  unitnum = _unitnum;
  team = _team;
  name = "Player" + std::to_string(unitnum);
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
Weapons::Gun* Player::getGun() {
  return gun;
}
void Player::setGun(Weapons::Gun *_gun) {
  gun = _gun;
}

