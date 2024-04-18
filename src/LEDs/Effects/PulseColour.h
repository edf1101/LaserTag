/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This LED effect is just a pulsing colour for its duration.
*/

#ifndef LASERTAG_PULSECOLOUR_H
#define LASERTAG_PULSECOLOUR_H

#include "LEDEffect.h"

namespace LEDs {

    class PulseColour : public LEDEffect {
    public:
        PulseColour(){
          effectLength = 5000;
        }
        void updateLEDs(); // draw to the LEDs

    protected:
    };

} // LEDs

#endif //LASERTAG_PULSECOLOUR_H
