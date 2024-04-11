/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class controls and holds all logic & variables for the sound player.
*/

#include "SoundPlayer.h"

using namespace Sounds;

// Define sounds here
XT_Wav_Class SoundPlayer::TestSound =  XT_Wav_Class(TestWAV);

void SoundPlayer::soundLoop() {
// This is called every main system loop
    DacAudio.FillBuffer();                // Fill the sound buffer with data
}

void SoundPlayer::playSound(XT_PlayListItem_Class *sound) {
  DacAudio.Play(sound);
}

