/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This header file holds references to all the weapons in the game. You add new weapons here.
*/

#ifndef LASERTAG_WEAPONS_H
#define LASERTAG_WEAPONS_H

#include "Arduino.h"
#include <string>
#include <unordered_map>
#include "Gun.h" // For creating Gun types
#include "../Displays/ImageData.h" // For getting gun images

class GunTypes {
public:
    Weapons::Gun *getGun(const std::string &gunName) {
      // Get a pointer to a gun by its name
      for (auto &gun: allGuns) {
        if (gun->getName() == gunName) {
          return gun;
        }
      }
    }

    Weapons::Gun *getGun(int gunId) {
      // Get a pointer to a gun by its index
      for (auto &gun: allGuns) {
        if (gun->getIndex() == gunId) {
          return gun;
        }
      }
    }

private:
    // Define the different Guns here (Don't modify default guns or anti-cheat will get you:
    Weapons::Gun AssaultRifle = Weapons::Gun(0, "Assault Rifle", "AR",
                                             Images::img_bullet,
                                             16, 10, 2000,
                                             Weapons::ReloadType::AUTO, 20,
                                             300, 100, 400,
                                             -1, false, 1);

    Weapons::Gun SMG = Weapons::Gun(0, "SMG", "SMG",
                                    Images::img_bullet,
                                    16, 10, 2000,
                                    Weapons::ReloadType::AUTO, 15,
                                    150, 75, 250,
                                    3, false, 0.8);

    // Put all the guns created into this array (order doesn't matter)
    Weapons::Gun *allGuns[2] = {&AssaultRifle, &SMG};


};

#endif //LASERTAG_WEAPONS_H
