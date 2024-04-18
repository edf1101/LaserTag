/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This file manages weapons within the game
*/

#include "WeaponsManager.h"

#include <utility>
#include <algorithm>

using namespace Weapons;

Weapons::Gun *WeaponsManager::getGun(const std::string &gunName) {
  // Get a pointer to a gun by its name

  findAllGuns(); // make sure the list of guns is up-to-date

  for (auto &gun: allGuns) {
    Serial.println(gun->getName().c_str());
    if (gun->getName() == gunName) {
      return gun;
    }
  }

  throw std::invalid_argument("Gun not found");
}

Weapons::Gun *WeaponsManager::getGun(int gunId) {
  // Get a pointer to a gun by its index

  findAllGuns(); // make sure the list of guns is up-to-date

  for (auto &gun: allGuns) {
    if (gun->getIndex() == gunId) {
      return gun;
    }
  }
  throw std::invalid_argument("Gun not found");
}

void WeaponsManager::findAllGuns() {
  // Collate all the guns in active gun groups

  std::vector<int> checkedIds; // store the ids of the guns we have already added

  allGuns.clear(); // empty the list
  for (auto &gunGroup: allGunGroups) {

    if (!gunGroup->getInUse()) { // skip this group if it's not in use
      continue;
    }

    for (auto &gun: gunGroup->getWeapons()) { // add all the guns from this group
      if (std::count(checkedIds.begin(), checkedIds.end(), gun->getIndex())){
        continue; // skip this gun if we have already added it
      }
      allGuns.push_back(gun);
    }
  }

  // If there are no guns (ie no groups selected) then add the default gun
  if (allGuns.empty()) {
    allGuns.push_back(&AssaultRifle);
  }
}

Weapons::GunGroup *WeaponsManager::getGunGroup(int groupIndex) {
  // Get a pointer to a gun group by its index

  for (auto &gunGroup: allGunGroups) {
    if (gunGroup->getIndex() == groupIndex) {
      return gunGroup;
    }
  }
  throw std::invalid_argument("Group not found");
}

Weapons::GunGroup *WeaponsManager::getGunGroup(std::string groupName) {
  // Get a pointer to a gun group by its name

  for (auto &gunGroup: allGunGroups) {
    if (gunGroup->getName() == groupName) {
      return gunGroup;
    }
  }
  throw std::invalid_argument("Group not found");
}

void WeaponsManager::setGroupUseState(std::string groupName, bool state) {
  // Set whether a group is in use or not
  getGunGroup(std::move(groupName))->setInUse(state);
}

std::vector<Weapons::Gun *> WeaponsManager::getAllGuns() {
  // Return all active guns
  findAllGuns();
  return allGuns;
}
