/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This class holds a set of guns as a group
*/

#ifndef LASERTAG_GUNGROUP_H
#define LASERTAG_GUNGROUP_H

#include <vector>
#include <string>
#include "Gun.h"

namespace Weapons {

    class GunGroup {
    public:
        GunGroup(int groupIndex, std::string groupName, std::vector<Weapons::Gun*> weapons, bool inUse = false);

        std::vector<Weapons::Gun*> getWeapons(); // return the weapons

        std::string getName(); // Get the name
        int getIndex() const; // Getter for the index

        void calculateHash(); // calculate the combined hash of the weapons
        int getHash(); // return the hash

        void setInUse(bool inUse); // Set whether this group is in use
        bool getInUse(); // Get whether this group is in use
    private:
        int groupIndex; // The index we reference this group by
        std::string groupName; // The name of this group

        std::vector<Weapons::Gun*> weapons; // The weapons contained in this group

        int weaponsHash = 0; // stores the combined hash of the weapons

        bool inUse = false; // Whether this group is in use

    };

} // Weapons

#endif //LASERTAG_GUNGROUP_H
