/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This class represents a basic gun object.
*/

#ifndef LASERTAG_GUN_H
#define LASERTAG_GUN_H

#include <string>
#include <functional>
#include "../Displays/ImageData.h"
#include "../Sound/SoundData.h"

namespace Weapons { // So we don't have irrelevant things floating around in the global namespace

#define PRESSES_TO_RELOAD 2 // How many times you need to press the reload button to reload all mags

    enum ReloadType {
        AUTO, // Don't need to press anything to reload
        PRESS_FOR_ALL, // Need to press a button to reload all mags
        PRESS_PER_BULLET // Need to press a button to reload each bullet (when you fire again it stops reloading)
    };

    // This defines the different fire rates a gun can have
    enum FireRate {
        NORMAL, // The gun's normal fire rate
        FAST, // The gun's fast fire rate
        SLOW // The gun's slow fire rate
    };

    enum InfiniteAmmoState {
        INFINITE_AMMO, // The gun has infinite ammo
        INFINITE_MAGS, // The gun has infinite mags
        NORMAL_AMMO // The gun has normal Ammo and Mags
    };

    class Gun {
        // This class represents a gun
    public:
        Gun(int gunId, std::string gunName, std::string gunAcronym,
            Images::ImageData gunImage,
            int magSize, int magStartCount, int magReloadTime, ReloadType magReloadType,
            int damage,
            int fireRateNormal, int fireRateFast, int fireRateSlow,
            int shotsPerBurst, bool defaultSuppressed, float volume,
             Sounds::SoundData gunSound);

        void resetCharacteristics(); // Reset the gun's characteristics to default
        int getIndex() const; // Returns the gun's index

        bool tryFire(); // if the gun can fire (not reloading etc.), it fires and returns true, otherwise returns false
        void resetBurstCount(); // Resets the burst count (when trigger released)

        bool getSuppressed(); // Get whether the gun is suppressed
        void setSuppressed(bool _suppressed); // Set whether the gun is suppressed

        void reloadLoop(); // The loop that deals with reloading logic
        void reloadAddBullet();

        bool getReloading(); // Get whether the gun is currently reloading

        void setFireRate(FireRate _fireRate); // Set the fire rate of the gun

        std::string getName(); // Get the gun's name
        std::string getAcronym(); // Get the guns acronym
        std::string getReloadDescription(); // Get the description of how the gun reloads

        Sounds::SoundData getSound(); // Get the gun's sound effect so it can be played back elsewhere
        int getDamage(); // Get the gun's damage

        int getAmmoRemaining(); // Get the remaining ammo in the mag currently
        int getMagsRemaining(); // get the mags left for the gun

        int getInitialMags(); // Get the number of mags the gun starts with
        int getInitialAmmo(); // Get the number of bullets the gun starts with

        void setAmmoAndMags(int ammo, int mags); // Set the ammo and mags for the gun


        int createHash(); // Create a hash of the gun's characteristics for the anti-cheat system

        void setHUDFunction(std::function<void(void)> _drawHUD); // Set the function to draw the gun's HUD

        int getFireSpeed(); // Get the fire speed of the gun
        std::string getFireType() const; // Get the fire type of the gun

        Images::ImageData getImage(); // Get the gun's image

        void setInfiniteAmmoState(InfiniteAmmoState infiniteState); // Set whether the gun has infinite ammo
        InfiniteAmmoState getInfiniteAmmoState(); // Get whether the gun has infinite ammo


    private:
        // Gun default Characteristics
        int gunID; // The ID of the gun
        std::string gunName; // The name of the gun
        std::string gunAcronym; // The short name to display on the HUD eg. AR, SMG
        Images::ImageData gunImage; // The image of the gun

        int magSize; // How many bullets in each mag
        int magStartCount; // How many mags the gun starts with
        int magReloadTime; // How long it takes to reload the mag
        ReloadType magReloadType; // Whether the gun reloads the mag automatically, press for all at once or press by bullet
        std::string reloadDescription; // The description of how the gun reloads (used for HUD info screen)

        int damage; // How much damage each bullet does

        int fireRateNormal; // How fast the gun can shoot normally
        int fireRateFast; // How fast the gun can shoot if set to fast mode
        int fireRateSlow; // How fast the gun can shoot if set to slow mode
        int shotsPerBurst; // How many shots per time you hold the trigger (-1 for full auto)

        bool defaultSuppressed; // Whether the gun is suppressed by default
        float volume; // The volume of the gun (0-1)
         Sounds::SoundData gunSound;

        // Gun instance variables
        int magsRemaining; // How many mags are left
        int bulletsInMag; // How many bullets are left in the mag

        bool reloading; // Whether the gun is currently reloading
        long reloadStartTime = 0; // The time the gun started reloading (used for guns with auto reload)
        int reloadCount; // How many times reload button has been pressed (for guns with press all or press bullet)

        int fireRate; // The current fire rate of the gun
        long lastFired = 0; // The time the gun last fired (used to check if can fire)
        int burstCount; // How many shots have been fired in the current burst

        bool suppressed; // Whether the gun is currently suppressed

        std::function<void(void)> drawHUD; // Function to draw the gun's HUD

        // infinite ammo / mags
        InfiniteAmmoState currentAmmoState = NORMAL_AMMO; // The current state of the gun's ammo
    };
}

#endif //LASERTAG_GUN_H
