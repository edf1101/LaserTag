/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class controls and holds all logic & variables for the sound player.
*/

#include "SoundPlayer.h"

using namespace Sounds;

void SoundPlayer::init() {
  // Initialises the sound system.

  // set up the I2S output
  out = new AudioOutputI2S();
  out->SetPinout(AMP_BCLK, AMP_LRCLK, AMP_DATA);
  setVolume(1); // set the volume to max

  // set up the WAV generator
  wav = new AudioGeneratorWAV();
}

void SoundPlayer::soundLoop() {
  // This is called every main system loop to fill the sound buffer
#if SOUND_ON

  if (wav->isRunning()) { // calls the buffer if the sound is running, if finished it will stop the sound
    if (!wav->loop()) wav->stop();
  }
#endif
}

void SoundPlayer::playSound(SoundData sound) {
  // Play a sound

#if SOUND_ON
  // stop the old sound if its running
  if (wav->isRunning()) {
    wav->stop();
  }

  // set up the new wav
  file = new AudioFileSourcePROGMEM(sound.mySound, sound.length);
  wav->begin(file, out);
#endif
}

void SoundPlayer::setVolume(float volume) {
  // Set the volume of the sound 0-1

  volume = max(0.0f, min(0.99f, volume)); // Clamp the volume between 0 and 1

  out->SetGain(volume * 4); // SetGain is between 0 and 4, so we multiply by 4 and apply

}


