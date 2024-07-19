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
  out->SetPinout(0,25,19);
  out->SetGain(3.0);

  // set up the WAV generator
  wav = new AudioGeneratorWAV();
}

void SoundPlayer::soundLoop() {
  // This is called every main system loop to fill the sound buffer

  if (wav->isRunning()) { // calls the buffer if the sound is running, if finished it will stop the sound
    if (!wav->loop()) wav->stop();
  }

}

void SoundPlayer::playSound(SoundData sound) {
  // Play a sound

  // stop the old sound if its running
  if (wav->isRunning()){
    wav->stop();
  }

  // set up the new wav
  file = new AudioFileSourcePROGMEM( sound.mySound, sound.length );
  wav->begin(file, out);
}


