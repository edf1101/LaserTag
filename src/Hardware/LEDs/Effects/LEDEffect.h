/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This class represents an effect on the LEDs.
 * It is abstract and Effect implementations will inherit from this.
*/

#ifndef LASERTAG_LEDEFFECT_H
#define LASERTAG_LEDEFFECT_H

#include "Arduino.h"
#include "../../../Libs/Adafruit_NeoPixel/Adafruit_NeoPixel.h"

namespace LEDs {

    class LEDEffect {
    public:
        virtual void startEffect(); // start the effect
        bool getEffectFinished(); // get if the effect is done running
        virtual void updateLEDs(); // update the LED colour

        uint32_t getPixel(int pos) { return effectBuffer[pos]; }

        void setColour(uint32_t _colour) { colour = _colour; } // set the colour
        void setInfinite(bool infiniteState); // set if effect is infinite
        virtual void setLength(unsigned long newLength);

    protected:
        uint32_t effectBuffer[5];

        uint32_t colour = Adafruit_NeoPixel::Color(255, 255, 255);


        unsigned long startTime = 0;
        unsigned long effectLength = 1000;
        bool infinite = false;

        static uint8_t getRComponent(uint32_t col);

        static uint8_t getGComponent(uint32_t col);

        static uint8_t getBComponent(uint32_t col);

        static uint32_t setBrightness(uint32_t col, float brightness);
    };

} // LEDs

#endif //LASERTAG_LEDEFFECT_H
