/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class handles firing the gun and detecting hits, Higher level version of Infrared.
*/

#ifndef LASERTAG_FIRING_H
#define LASERTAG_FIRING_H

#include <Arduino.h>
#include "Infrared.h"
#include "../config.h"
#include "../Players/PlayerWrapper.h"
#include "Weapons/WeaponsManager.h"
#include "../Buttons/Buttons.h"

class LaserTag; // Forward declaration

#define MUZZLE_FLASH_TIME 50 // Time in ms for the muzzle flash to be on
#define VIBRATE_TIME 200 // Time in ms for the muzzle flash to be on

class Firing {
public:
    explicit Firing(LaserTag *_mySystem); // Constructor
    void FiringLoop(); // Main loop function
    void sendCommand(uint16_t command); // Function to send a command to another gun
    void Fire(); // Function to send a hit signal to another gun

private:
    LaserTag *mySystem; // The system object
    Buttons *gameButtons;
    Infrared infraredTransciever;  // infrared object
    void OnHit(); // Function to call when a hit packet is received
    void OnCommand(); // Function to call when a control packet is received

    void OnTriggerUp();

    void OnMagazineButtonDown();

    bool muzzleFlash = false; // Is the muzzle flash on
    unsigned long lastMuzzleFlash = 0; // The time it turned on

    bool allowVibrations =true;
    bool vibrating = false;
    unsigned long lastVibrate = 0;

    unsigned long lastTurnOffNeopixels; // used to reactivate neopixels after a period of firing
};


#endif //LASERTAG_FIRING_H
