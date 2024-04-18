/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This file manages weapons within the game
*/

#ifndef LASERTAG_WEAPONSMANAGER_H
#define LASERTAG_WEAPONSMANAGER_H

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "Arduino.h"
#include "Gun.h" // For creating Gun types
#include "../Displays/ImageData.h" // For getting gun images
#include "../Sound/SoundPlayer.h" // For getting gun sounds
#include "GunGroup.h"

class WeaponsManager {
public:
    Weapons::Gun *getGun(const std::string &gunName); // references a gun by its name
    Weapons::Gun *getGun(int gunId); // references a gun by its index


    void setGroupUseState(std::string groupName, bool state); // Set a groups use state
    std::vector<Weapons::Gun *> getAllGuns(); // return all active guns
private:
    Weapons::GunGroup *getGunGroup(int groupIndex); // references a gun group by its index
    Weapons::GunGroup *getGunGroup(std::string groupName); // references a gun group by its name

    void findAllGuns(); // collates all the guns in active gun groups
    std::vector<Weapons::Gun*> allGuns; // contains all guns

    // Define the different Guns here (Don't modify default guns or anti-cheat will get you:

    // DEFAULT GUNS (DO NOT MODIFY)
    Weapons::Gun AssaultRifle = Weapons::Gun(0, "Assault Rifle", "AR",
                                             Images::img_bullet,
                                             16, 10, 2000,
                                             Weapons::ReloadType::AUTO, 20,
                                             300, 100, 400,
                                             -1, false, 1,
                                             &Sounds::SoundPlayer::ArSound);

    Weapons::Gun SMG = Weapons::Gun(1, "SMG", "SMG",
                                    Images::img_bullet,
                                    16, 10, 2000,
                                    Weapons::ReloadType::AUTO, 15,
                                    150, 75, 250,
                                    3, false, 0.8,
                                    &Sounds::SoundPlayer::SmgSound);

    Weapons::Gun Sniper = Weapons::Gun(2, "Sniper", "SN",
                                       Images::img_bullet,
                                       2, 20, 5000,
                                       Weapons::ReloadType::PRESS_PER_BULLET, 80,
                                       150, 75, 250,
                                       1, false, 0.2,
                                       &Sounds::SoundPlayer::PistolSound);

    Weapons::Gun Shotgun = Weapons::Gun(3, "Shotgun", "SG",
                                        Images::img_bullet,
                                        8, 10, 5000,
                                        Weapons::ReloadType::PRESS_FOR_ALL, 50,
                                        150, 75, 250,
                                        1, false, 1,
                                        &Sounds::SoundPlayer::ShotgunSound);

    // Pistol Guns
    // TODO add actual sound effects
    Weapons::Gun Glock = Weapons::Gun(4, "Glock-18", "GLK",
                                       Images::img_bullet,
                                       12, 10, 5000,
                                       Weapons::ReloadType::PRESS_FOR_ALL, 10,
                                       100, 75, 250,
                                       3, false, 0.7,
                                       &Sounds::SoundPlayer::PistolSound);

    Weapons::Gun supressedPistol = Weapons::Gun(4, "Supressed Pistol", "SUP",
                                                Images::img_bullet,
                                                10, 10, 5000,
                                                Weapons::ReloadType::PRESS_FOR_ALL, 25,
                                                250, 140, 400,
                                                1, true, 0.7,
                                                &Sounds::SoundPlayer::PistolSound);

    Weapons::Gun desertEagle = Weapons::Gun(4, "Desert Eagle", "DEG",
                                                Images::img_bullet,
                                                8, 12, 5000,
                                                Weapons::ReloadType::PRESS_FOR_ALL, 50,
                                                600, 400, 800,
                                                1, false, 1.0,
                                                &Sounds::SoundPlayer::PistolSound);

    Weapons::Gun mac11 = Weapons::Gun(4, "MAC11", "MAC",
                                            Images::img_bullet,
                                            20, 7, 5000,
                                            Weapons::ReloadType::PRESS_FOR_ALL, 7,
                                            250, 125, 400,
                                            -1, false, 0.7,
                                            &Sounds::SoundPlayer::PistolSound);


    // define the gun groups here
    std::vector<Weapons::Gun*> defaults = {&AssaultRifle, &SMG, &Sniper, &Shotgun};
    Weapons::GunGroup defaultGroup = Weapons::GunGroup(0,"Default", defaults, true);

    std::vector<Weapons::Gun*> pistols = {&Glock, &supressedPistol, &desertEagle, &mac11};
    Weapons::GunGroup pistolGroup = Weapons::GunGroup(1,"Pistols", pistols);

    // Put all the gun groups created into this array (order doesn't matter) contains USED AND UNUSED gun groups
    Weapons::GunGroup *allGunGroups[2] = {&defaultGroup, &pistolGroup};



};

#endif //LASERTAG_WEAPONSMANAGER_H
