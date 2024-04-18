/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This class holds a set of guns as a group
*/

#include "GunGroup.h"

#include <utility>

namespace Weapons {
    GunGroup::GunGroup(int groupIndex, std::string groupName, std::vector<Weapons::Gun *> weapons, bool inUse) {
      this->groupName = std::move(groupName);
      this->groupIndex = groupIndex;
      this->weapons = std::move(weapons);
      this->inUse = inUse;

      calculateHash(); // calculate the hash of the weapons based on the first time they are added
    }

    std::vector<Weapons::Gun *> GunGroup::getWeapons() {
      // Getter for the weapons
      return weapons;
    }

    std::string GunGroup::getName() {
      // getter for group name
      return groupName;
    }

    int GunGroup::getIndex() const {
      // getter for the group index
      return groupIndex;
    }

    void GunGroup::calculateHash() {
      // calculate the combined hash of the weapons

      weaponsHash = 0;
      for (Weapons::Gun *gun: weapons) {
        weaponsHash += gun->createHash();
      }
    }

    int GunGroup::getHash() {
      // getter for the hash
      return weaponsHash;
    }

    void GunGroup::setInUse(bool inUse) {
      // Sets whether the group is in use or not
      this->inUse = inUse;
    }

    bool GunGroup::getInUse() {
      // Getter for whether the group is in use
      return inUse;
    }
} // Weapons
