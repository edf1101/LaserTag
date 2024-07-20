/*
 * Created by Ed Fillingham on 20/07/2024.
 *
 * This manages some of the more simplistic, basic hardware functions.
 * This includes pins on GPIO expander and latch powering on/ off.
*/

#ifndef LASERTAG_HARDWARE_H
#define LASERTAG_HARDWARE_H

#include "Arduino.h"
#include <Adafruit_MCP23X08.h>
#include "../config.h"

class Hardware {
public:
    static void init(); // Initialises the hardware objects this class controls

    static void loop(); // Loops the hardware objects this class controls (used for powering off only)

    static void pinModeExp(uint8_t pin, uint8_t mode);

    static bool digitalReadExp(uint8_t pin);

    static void digitalWriteExp(uint8_t pin, uint8_t value);

    static void turnOffSystem(unsigned long delay = 1500);

    static uint8_t findOLEDAddress();

private:
    inline static Adafruit_MCP23X08 mcp; // the I2C expander object

    // variables for turning off the gun
    inline static bool turnedOff = false;
    inline static unsigned long turnOffTime = 0;
    inline static unsigned long turnOffDelay = 1500; // 5 seconds
};


#endif //LASERTAG_HARDWARE_H
