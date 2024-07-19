/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class controls and holds all logic & variables for the sound player.
*/

#ifndef FIRING_CPP_SOUNDPLAYER_H
#define FIRING_CPP_SOUNDPLAYER_H



#include "Arduino.h"
#include "../config.h"
#include "../Libs/ESP8266Audio/src/AudioFileSourcePROGMEM.h"
#include "../Libs/ESP8266Audio/src/AudioGeneratorWAV.h"
#include "../Libs/ESP8266Audio/src/AudioOutputI2S.h"
#include "SoundData.h"

namespace Sounds {

#include "Sounds/ArSound.h"


    class SoundPlayer {
    public:
        void init(); // Initialises the buffers, I2S output and WAV generator
        void soundLoop(); // This is called every main system loop to fill the sound buffer

        void playSound(SoundData sound); // Play a sound



    private:
        // Create the sound low level object

        AudioGeneratorWAV *wav;
        AudioFileSourcePROGMEM *file;
        AudioOutputI2S *out;

    };
}


#endif //FIRING_CPP_SOUNDPLAYER_H
