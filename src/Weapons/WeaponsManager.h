/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This file manages weapons within the game
*/

#ifndef LASERTAG_WEAPONSMANAGER_H
#define LASERTAG_WEAPONSMANAGER_H

#include <functional>
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
    static Weapons::Gun getGun(const std::string &gunName); // references a gun by its name
    static Weapons::Gun getGun(int gunId); // references a gun by its index


    static void setGroupUseState(std::string groupName, bool state); // Set a groups use state
    static std::vector<Weapons::Gun> getAllGuns(); // return all active guns

    static std::vector<Weapons::GunGroup*> getGunGroups(); // return all gun groups

    static void setUpdateMenuCallback(std::function<void(void)> callback); // set the callback function for updating the menu of changes

    static void setGunsSwappable(bool swappable); // set whether the guns are swappable or not
    static bool getGunsSwappable(); // get whether the guns are swappable or not

    inline static std::string defaultGun = "Assault Rifle"; // the default gun to use

private:
    inline static std::function<void(void)> updateMenuOfChanges; // function to update the menu of changes
    inline static bool setCallback = false;

    static Weapons::GunGroup *getGunGroup(int groupIndex); // references a gun group by its index
    static Weapons::GunGroup *getGunGroup(std::string groupName); // references a gun group by its name

    static void findAllGuns(); // collates all the guns in active gun groups
    inline static std::vector<Weapons::Gun> allGuns; // contains all guns

    inline static bool gunsSwappable = true; // whether the guns are swappable or not

    // Define the different Guns here (Don't modify default guns or anti-cheat will get you:

    // DEFAULT GUNS (DO NOT MODIFY)
    inline static Weapons::Gun AssaultRifle = Weapons::Gun(0, "Assault Rifle", "AR",
                                             Images::img_gunAR,
                                             16, 10, 2000,
                                             Weapons::ReloadType::AUTO, 20,
                                             300, 100, 400,
                                             -1, false, 1,
                                             &Sounds::SoundPlayer::ArSound);

    inline static Weapons::Gun SMG = Weapons::Gun(1, "SMG", "SMG",
                                    Images::img_gunMAC11,
                                    16, 10, 2000,
                                    Weapons::ReloadType::AUTO, 15,
                                    150, 75, 250,
                                    3, false, 0.8,
                                    &Sounds::SoundPlayer::SmgSound);

    inline static Weapons::Gun Sniper = Weapons::Gun(2, "Sniper", "SN",
                                       Images::img_gunSniper,
                                       2, 20, 5000,
                                       Weapons::ReloadType::PRESS_PER_BULLET, 80,
                                       150, 75, 250,
                                       1, false, 0.2,
                                       &Sounds::SoundPlayer::SniperSound);

    inline static Weapons::Gun Shotgun = Weapons::Gun(3, "Shotgun", "SG",
                                        Images::img_gunShotgun,
                                        8, 10, 5000,
                                        Weapons::ReloadType::PRESS_FOR_ALL, 50,
                                        150, 75, 250,
                                        1, false, 1,
                                        &Sounds::SoundPlayer::ShotgunSound);

    // Pistol Guns
    inline static Weapons::Gun Glock = Weapons::Gun(4, "Glock-18", "GLK",
                                       Images::img_gunPistol,
                                       12, 10, 5000,
                                       Weapons::ReloadType::PRESS_FOR_ALL, 10,
                                       100, 75, 250,
                                       3, false, 0.7,
                                       &Sounds::SoundPlayer::GlockSound);

    inline static Weapons::Gun supressedPistol = Weapons::Gun(4, "P250-SUP", "SUP",
                                                Images::img_gunPisSupp,
                                                10, 10, 5000,
                                                Weapons::ReloadType::PRESS_FOR_ALL, 25,
                                                250, 140, 400,
                                                1, true, 0.2,
                                                &Sounds::SoundPlayer::SmgSound);

    inline static Weapons::Gun desertEagle = Weapons::Gun(4, "Desert Eagle", "DEG",
                                                Images::img_gunPistol,
                                                8, 12, 5000,
                                                Weapons::ReloadType::PRESS_FOR_ALL, 50,
                                                600, 400, 800,
                                                1, false, 1.0,
                                                &Sounds::SoundPlayer::DeagleSound);

    inline static Weapons::Gun mac11 = Weapons::Gun(4, "MAC11", "MAC",
                                            Images::img_gunMAC11,
                                            20, 7, 5000,
                                            Weapons::ReloadType::PRESS_FOR_ALL, 7,
                                            250, 125, 400,
                                            -1, false, 0.7,
                                            &Sounds::SoundPlayer::GlockSound);


    // define the gun groups here
    inline static std::vector<Weapons::Gun*> defaults = {&AssaultRifle, &SMG, &Sniper, &Shotgun};
    inline static Weapons::GunGroup defaultGroup = Weapons::GunGroup(0,"Default", defaults, true);

    inline static std::vector<Weapons::Gun*> pistols = {&Glock, &supressedPistol, &desertEagle, &mac11};
    inline static Weapons::GunGroup pistolGroup = Weapons::GunGroup(1,"Pistols", pistols, true);

    // Put all the gun groups created into this array (order doesn't matter) contains USED AND UNUSED gun groups
    inline static Weapons::GunGroup *allGunGroups[2] = {&defaultGroup, &pistolGroup};



};

#endif //LASERTAG_WEAPONSMANAGER_H

