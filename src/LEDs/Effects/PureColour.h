/*
 * Created by Ed Fillingham on 18/04/2024.
 *
 * This LED effect is just a solid colour for its duration.
*/

#ifndef LASERTAG_PURECOLOUR_H
#define LASERTAG_PURECOLOUR_H

#include "LEDEffect.h"

namespace LEDs {

    class PureColour : public LEDEffect {
    public:
        PureColour(){
          effectLength = 5000;
        }

        void updateLEDs(); // draw to the LEDs

    protected:
    };

} // LEDs

#endif //LASERTAG_PURECOLOUR_H
