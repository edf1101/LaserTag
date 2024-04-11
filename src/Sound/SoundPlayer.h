/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class controls and holds all logic & variables for the sound player.
*/

#ifndef FIRING_CPP_SOUNDPLAYER_H
#define FIRING_CPP_SOUNDPLAYER_H

#include "Arduino.h"
#include "XT_DAC_Audio.h"
#include "../Pins.h"

namespace Sounds {

#include "Sounds/TestSound.h"

    class SoundPlayer {
    public:
        void soundLoop(); // This is called every main system loop to fill the sound buffer

        void playSound(XT_PlayListItem_Class *sound); // Play a sound

        // declare all sounds here, then declare them in the .cpp file
        static XT_Wav_Class TestSound;

    private:
        // Create the sound low level object
        XT_DAC_Audio_Class DacAudio = XT_DAC_Audio_Class(DAC_PIN, 0);

    };
}


#endif //FIRING_CPP_SOUNDPLAYER_H
