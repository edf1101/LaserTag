/*
 * Created by Ed Fillingham on 07/04/2024.
 *
 * This is the basic entrance file for the Laser Tag project.
 * It initializes the LaserTag object and calls the loop function repeatedly.
 */

#include <Arduino.h>
#include "LaserTag.h"

LaserTag laserTag;

void setup() {
    // Gets called once at the start of the program

    laserTag.init();
}

void loop() {
    // Gets called repeatedly by the microcontroller

    laserTag.loop();
}
