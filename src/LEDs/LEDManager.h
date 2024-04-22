/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This class handles the cosmetic LEDs (neopixel strips etc.)
*/

#ifndef LASERTAG_LEDMANAGER_H
#define LASERTAG_LEDMANAGER_H

#include <stack>
#include "Arduino.h"
#include "../Adafruit_NeoPixel/Adafruit_NeoPixel.h"
#include "../config.h"
#include "AllLEDEffects.h"

#define NEOPIXEL_UPDATE_INTERVAL 100
namespace LEDs {

    class LEDManager {
    public:
        void init(); // semi constructor to set up the fastLED object.
        void loop(); // update the current effect.

        void setLEDState(bool state); // set whether the LEDs are allowed to be on or not

        void pushLEDEffect(LEDEffect *effect); // set a new LED effect

    private:

        Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXEL_LEDS_COUNT, NEOPIXEL_LEDS_PIN, NEO_GRB + NEO_KHZ800);

        // variables pointing to the current effect in use and whether it has been set(to avoid null pointer errors)
        std::stack<LEDEffect*> effectStack;

        bool ledsOn = true;

        // last time we checked LEDs, only check every so often so we don't call complex functions too often
        unsigned long lastUpdate;
    };

} // LEDs

#endif //LASERTAG_LEDMANAGER_H
