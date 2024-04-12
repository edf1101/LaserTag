/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class controls and holds all logic & variables for the entire gun / game.
 * The main.cpp or .ino file just calls this object's void init() instead of void setup()
 * and this object's void loop() instead of its own.
*/

#include "LaserTag.h"

void LaserTag::init() {
  // This gets called once at the start of the program

  Serial.begin(9600); // start serial communication for debug purposes

  // Set up the player object
  player.init(1, 1); // Create a player object with unitnum 1 and team 1

  // set up the displays
  hudDisplay.init();
  sideDisplay.init();

  currentGame.drawHUD();

}


void LaserTag::loop() {
  // This gets called everytime the loop() function is called in the main.cpp / LaserTag.ino file

  soundPlayer.soundLoop(); // Check if any sounds need to be played / fill buffer
  sideDisplay.pollEncoder(); // Check the rotary encoder for movements
  buttons.pollButtons(); // Check the buttons for presses
  firing.FiringLoop(); // Call the firing loop function
  player.loop(); // Call the player loop function
}

// Pointer Getters for the main objects so they can be accessed elsewhere
Player *LaserTag::getPlayer() {
  // returns a pointer to the player object
  return &player;
}

Buttons *LaserTag::getButtons(){
  // returns a pointer to the trigger button object
  return &buttons;
}

Sounds::SoundPlayer *LaserTag::getSoundPlayer(){
  // returns a pointer to the sound player object
  return &soundPlayer;
}

Gamemode *LaserTag::getGamemode() {
  return &currentGame;
}

HudDisplay *LaserTag::getHudDisplay() {
  return &hudDisplay;
}
