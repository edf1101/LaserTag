/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This class handles the cosmetic LEDs (neopixel strips etc)
*/

#include "LEDManager.h"

namespace LEDs {
    void LEDManager::init() {
      // semi constructor to set up the FastLED object
      pixels.begin();
      pixels.setBrightness(60); // save power don't have the pixels very bright
    }

    void LEDManager::setLEDState(bool state) {
      // Turns the LEDs on or off.
      ledsOn = state;
      if (!state) {
        pixels.clear();
        pixels.show();
      }
    }

    void LEDManager::loop() {
      // update the current effect.

      if (millis() - lastUpdate < NEOPIXEL_UPDATE_INTERVAL) { return; } // return if set recently
      lastUpdate = millis();

      if (!ledsOn || !NEOPIXEL_ON || effectStack.empty()) { // return if not showing LEDS right now
        return;
      }

      if (effectStack.top()->getEffectFinished()) { // if effect is finished return
        pixels.clear();
        pixels.show();

        LEDEffect *oldValue = effectStack.top();
        effectStack.pop();
        delete oldValue;
        return;
      }

      // update effect LEDs
      effectStack.top()->updateLEDs();

      // draw to the LED strip
      for (int i = 0; i < NEOPIXEL_LEDS_COUNT; i++) {
        // code to split up LEDs if not using standard 5

        int queryPixel = (int) round(5 * i / NEOPIXEL_LEDS_COUNT);
        pixels.setPixelColor(i, effectStack.top()->getPixel(queryPixel));
      }
      pixels.show();
    }

    void LEDManager::pushLEDEffect(LEDEffect *effect) {
      // push an LED effect onto the stack

      effectStack.push(effect);
      effect->startEffect();
    }


} // LEDs