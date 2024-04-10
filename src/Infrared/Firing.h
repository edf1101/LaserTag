/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class handles firing the gun and detecting hits, Higher level version of Infrared.
*/

#ifndef LASERTAG_FIRING_H
#define LASERTAG_FIRING_H

//#include "../LaserTag.h"
#include "Infrared.h"
#include "../Pins.h"

class LaserTag; // Forward declaration

class Firing {
public:
    explicit Firing(LaserTag* _mySystem); // Constructor
    void FiringLoop(); // Main loop function
    void sendCommand(uint16_t command); // Function to send a command to another gun
    void Fire(); // Function to send a hit signal to another gun

private:
    LaserTag* mySystem; // The system object
    Infrared infraredTransciever;  // infrared object
    void OnHit(); // Function to call when a hit packet is received
    void OnCommand(); // Function to call when a control packet is received
};


#endif //LASERTAG_FIRING_H
