/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This class represents a basic gun object.
*/

#ifndef LASERTAG_GUN_H
#define LASERTAG_GUN_H

#include <string>
#include "XT_DAC_Audio.h"
#include "../Displays/ImageData.h"

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

    class Gun {
        // This class represents a gun
    public:
        Gun(int gunId, std::string gunName, std::string gunAcronym,
            Images::ImageData gunImage,
            int magSize, int magStartCount, int magReloadTime, ReloadType magReloadType,
            int damage,
            int fireRateNormal, int fireRateFast, int fireRateSlow,
            int shotsPerBurst, bool defaultSuppressed, float volume,
            XT_Wav_Class *gunSound
        );

        void resetCharacteristics(); // Reset the gun's characteristics to default
        int getIndex() const; // Returns the gun's index

        bool tryFire(); // if the gun can fire (not reloading etc.), it fires and returns true, otherwise returns false
        void resetBurstCount(); // Resets the burst count (when trigger released)

        bool getSuppressed(); // Get whether the gun is suppressed
        void setSuppressed(bool _suppressed); // Set whether the gun is suppressed

        void reloadLoop(); // The loop that deals with reloading logic
        void reloadAddBullet();

        void setFireRate(FireRate _fireRate); // Set the fire rate of the gun

        std::string getName(); // Get the gun's name
        std::string getAcronym(); // Get the guns acronym
        XT_Wav_Class *getSound(); // Get the gun's sound effect so it can be played back elsewhere
        int getDamage(); // Get the gun's damage
        int getAmmoRemaining(); // Get the remaining ammo in the mag currently
        int getMagsRemaining(); // get the mags left for the gun

        int createHash(); // Create a hash of the gun's characteristics for the anti-cheat system

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

        int damage; // How much damage each bullet does

        int fireRateNormal; // How fast the gun can shoot normally
        int fireRateFast; // How fast the gun can shoot if set to fast mode
        int fireRateSlow; // How fast the gun can shoot if set to slow mode
        int shotsPerBurst; // How many shots per time you hold the trigger (-1 for full auto)

        bool defaultSuppressed; // Whether the gun is suppressed by default
        float volume; // The volume of the gun (0-1)
        XT_Wav_Class *gunSound;

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
    };
}

#endif //LASERTAG_GUN_H
