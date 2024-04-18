/*
 * Created by Ed Fillingham on 18/04/2024.
*/

#include "PulseColour.h"
#include "../LEDManager.h"

namespace LEDs {

    void PulseColour::updateLEDs() {
      // set all the leds to one colour

      float percentThrough = remainder((float)(millis()-startTime) / (float)effectLength,1) ;

      float brightness = (float)(1+sin((percentThrough*PI*6.0) - (PI/2.0)))/2.0f;

      for (int i = 0; i < 5; i++) {
        effectBuffer[i] = setBrightness( colour,brightness);

      }
    }



} // LEDs