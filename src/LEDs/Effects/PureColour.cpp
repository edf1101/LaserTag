/*
 * Created by Ed Fillingham on 18/04/2024.
*/

#include "PureColour.h"

namespace LEDs {

    void PureColour::updateLEDs() {
      // set all the leds to one colour
      for (int i = 0; i < 5; i++) {
        effectBuffer[i] = colour;
      }
    }


} // LEDs