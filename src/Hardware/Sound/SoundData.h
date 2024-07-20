/*
 * Created by Ed Fillingham on 19/07/2024.
 *
 * This struct holds the sound data for the sound player to play.
*/

#ifndef LASERTAG_SOUNDDATA_H
#define LASERTAG_SOUNDDATA_H

#include "Arduino.h"

namespace Sounds {

    struct SoundData {
        const unsigned char *mySound; // Pointer to const unsigned char
        uint32_t length;

    };

}

#endif //LASERTAG_SOUNDDATA_H
