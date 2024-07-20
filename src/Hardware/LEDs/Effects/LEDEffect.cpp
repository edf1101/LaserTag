/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This class represents an effect on the LEDs.
 * It is abstract and Effect implementations will inherit from this.
*/

#include "LEDEffect.h"
#include "Arduino.h"

namespace LEDs {
    void LEDEffect::startEffect() {
      // Start the LED effect
      startTime = millis();
    }

    bool LEDEffect::getEffectFinished() {
      // Get if the effect has run its course.

      if (infinite) {
        return false;
      }

      return (millis() - startTime) > effectLength;
    }

    void LEDEffect::updateLEDs() {
    }

    uint32_t LEDEffect::setBrightness(uint32_t col, float brightness) {
      // set the brightness of a colour
      auto r = (uint8_t) ((float) getRComponent(col) * brightness);
      auto g = (uint8_t) ((float) getGComponent(col) * brightness);
      auto b = (uint8_t) ((float) getBComponent(col) * brightness);

      return Adafruit_NeoPixel::Color(r, g, b);
    }

    uint8_t LEDEffect::getRComponent(uint32_t col) {
      // extract the R component from a combined colour
      return (uint8_t) ((col >> 16) & 0xFF);
    }

    uint8_t LEDEffect::getGComponent(uint32_t col) {
      // extract the G component from a combined colour
      return (uint8_t) ((col >> 8) & 0xFF);
    }

    uint8_t LEDEffect::getBComponent(uint32_t col) {
      // extract the B component from a combined colour
      return (uint8_t) ((col >> 0) & 0xFF);
    }

    void LEDEffect::setInfinite(bool infiniteState) {
      // set if an effect is infinite
      infinite = infiniteState;
    }

    void LEDEffect::setLength(unsigned long newLength) {
      // set the length of an effect

      effectLength = newLength;
    }

} // LEDs