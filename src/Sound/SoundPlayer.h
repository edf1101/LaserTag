/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class controls and holds all logic & variables for the sound player.
*/

#ifndef FIRING_CPP_SOUNDPLAYER_H
#define FIRING_CPP_SOUNDPLAYER_H



#include "Arduino.h"
#include "XT_DAC_Audio.h"
#include "../config.h"

namespace Sounds {

#include "Sounds/ArSound.h"
#include "Sounds/PistolSound.h"
#include "Sounds/ShotgunSound.h"
#include "Sounds/SmgSound.h"
#include "Sounds/DeagleSound.h"
#include "Sounds/GlockSound.h"

    class SoundPlayer {
    public:
        void init(); // Initialise the sound player
        void soundLoop(); // This is called every main system loop to fill the sound buffer

        void playSound(XT_PlayListItem_Class *sound); // Play a sound

        // declare all sounds here, then declare them in the .cpp file
        static XT_Wav_Class ArSound;
        static XT_Wav_Class SmgSound;
        static XT_Wav_Class ShotgunSound;
        static XT_Wav_Class SniperSound;
        static XT_Wav_Class DeagleSound;
        static XT_Wav_Class GlockSound;

    private:
        // Create the sound low level object
#if SOUND_ON
        XT_DAC_Audio_Class DacAudio = XT_DAC_Audio_Class(DAC_PIN, 0);
        XT_PlayListItem_Class *currentSound = nullptr;
        bool highValue = false;
        long playIn;
        bool needsPlay;

        long offIn;
        bool needsOff;
#endif
    };
}


#endif //FIRING_CPP_SOUNDPLAYER_H
