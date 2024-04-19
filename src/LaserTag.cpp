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

#if DEBUG
  Serial.begin(115200); // start serial communication for debug purposes
  Serial.println("Started");
#endif
  // Set up the player object
  player.init(this, 121, 1); // Create a player object with unitnum 1 and team 1

  // set up the displays
  hudDisplay.init();
  sideDisplay.init();

  ledManager.init(); // set up the LED manager

  // Set up the gamemode manager after displays since it depends on the HUD
  gamemodeManager.init();

  gamemodeManager.switchGamemode(GamemodeManager::SOLO); // Set the initial gamemode to none
  gamemodeManager.getCurrentGame()->setGamePauseState(false); // Initialise the current gamemode

  updateHUD(); // Update the HUD to show the initial state of the game

}


void LaserTag::loop() {
  // This gets called everytime the loop() function is called in the main.cpp / LaserTag.ino file

  soundPlayer.soundLoop(); // Check if any sounds need to be played / fill buffer
  ledManager.loop();
  sideDisplay.pollEncoder(); // Check the rotary encoder for movements
  hudDisplay.loop(); // Call the HUD loop function
  buttons.pollButtons(); // Check the buttons for presses
  firing.FiringLoop(); // Call the firing loop function
  player.loop(); // Call the player loop function
  gamemodeManager.getCurrentGame()->loop(); // Call the current gamemode loop function

}

void LaserTag::updateHUD() {
//   Updates the Hud display

  getGamemode()->drawHUD();
}

bool LaserTag::canFire() {
  // Returns true if the player can fire
  return player.canFire() && getGamemode()->canFire();
}

bool LaserTag::canTakeDamage(int shooterUnitnum) {
  // Returns true if the player can take damage
  return getGamemode()->canTakeDamage(shooterUnitnum) && player.canTakeDamage(shooterUnitnum);
}

void LaserTag::turnOff() {
  // Turns off the gun with the latch circuit
  // TODO implement this once latch stuff done.
  Serial.println("Turning off");
}

// Pointer Getters for the main objects so they can be accessed elsewhere
PlayerWrapper *LaserTag::getPlayer() {
  // returns a pointer to the player object
  return &player;
}

Buttons *LaserTag::getButtons() {
  // returns a pointer to the trigger button object
  return &buttons;
}

Sounds::SoundPlayer *LaserTag::getSoundPlayer() {
  // returns a pointer to the sound player object
  return &soundPlayer;
}

Gamemode *LaserTag::getGamemode() {
// returns a pointer to the current game
  return gamemodeManager.getCurrentGame();
}

HudDisplay *LaserTag::getHudDisplay() {
  // returns a pointer to the HUD display object
  return &hudDisplay;
}

LEDs::LEDManager *LaserTag::getLEDManager() {
  return &ledManager;
}
