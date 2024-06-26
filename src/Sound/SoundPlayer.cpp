/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class controls and holds all logic & variables for the sound player.
*/

#include "SoundPlayer.h"

using namespace Sounds;

// Define sounds here
XT_Wav_Class SoundPlayer::ArSound = XT_Wav_Class(ARwav);
XT_Wav_Class SoundPlayer::SmgSound = XT_Wav_Class(SMGwav);
XT_Wav_Class SoundPlayer::ShotgunSound = XT_Wav_Class(shotgunWav);
XT_Wav_Class SoundPlayer::SniperSound = XT_Wav_Class(pistolWav);
XT_Wav_Class SoundPlayer::DeagleSound = XT_Wav_Class(Deaglewav);
XT_Wav_Class SoundPlayer::GlockSound = XT_Wav_Class(glockWav);

void SoundPlayer::soundLoop() {
// This is called every main system loop
#if SOUND_ON
  DacAudio.FillBuffer();                // Fill the sound buffer with data
#endif
}

void SoundPlayer::playSound(XT_PlayListItem_Class *sound) {
#if SOUND_ON
  DacAudio.Play(sound);
#endif
}

