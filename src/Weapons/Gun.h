/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This class represents a basic gun object.
*/

#ifndef LASERTAG_GUN_H
#define LASERTAG_GUN_H

#include <string>
#include "Displays/ImageData.h"

namespace Weapons { // So we don't have irrelevant things floating around in the global namespace

    enum ReloadType{
        AUTO, // Don't need to press anything to reload
        PRESS_ALL, // Need to press a button to reload all mags
        PRESS_BULLET // Need to press a button to reload each bullet (when you fire again it stops reloading)
    };

    class Gun {
        // This class represents a gun
    public:
        Gun(int gunId, std::string gunName, std::string gunAcronym,
            Images::ImageData gunImage,
            int magSize, int magStartCount, int magReloadTime, ReloadType magReloadType,
            int damage,
            int fireRateNormal, int fireRateFast, int fireRateSlow,
            int shotsPerBurst, bool defaultSuppressed, float volume
//            ,unsigned char *gunSound
            );
        void resetCharacteristics(); // Reset the gun's characteristics to default

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
        unsigned char *gunSound;

        // Gun instance variables
        int magsRemaining; // How many mags are left
        int bulletsInMag; // How many bullets are left in the mag

        bool reloading; // Whether the gun is currently reloading
        long reloadStartTime = 0; // The time the gun started reloading (used for guns with auto reload)
        int reloadCount; // How many times reload button has been pressed (for guns with press all)

        int fireRate; // The current fire rate of the gun
        long lastFired = 0; // The time the gun last fired (used to check if can fire)
        int burstCount; // How many shots have been fired in the current burst

        bool suppressed; // Whether the gun is currently suppressed

    };
}

#endif //LASERTAG_GUN_H
