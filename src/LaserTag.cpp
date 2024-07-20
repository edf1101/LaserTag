/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class controls and holds all logic & variables for the entire gun / game.
 * The main.cpp or .ino file just calls this object's void init() instead of void setup()
 * and this object's void loop() instead of its own.
*/

#include "LaserTag.h"
#include <utility>

using namespace Commands;

void LaserTag::init() {
  // This gets called once at the start of the program

  Logger::init(DEBUG_SERIAL, DEBUG_BAUD_RATE,
               Logger::LogLevel::DETAIL); // Set up the logger
  Logger::log(Logger::LogLevel::INFO, "Starting system...");
  networkManager.init(); // Set up the network manager

  // Set up the commands / command manager
  commandManager.setupCommands();

  // Set up the player object
  player.init(1); // Create a player object with unitnum 1 and team 1

  // set up the displays
  sideDisplay.init();
  hudDisplay.init();

  // set up the hardware class ASAP as it starts the power latch and that needs to be done fast
  Hardware::init();
  firing.init(); // Set up the firing object

  ledManager.init(); // set up the LED manager
  auto effect = new LEDs::PulseColour();
  effect->setInfinite(true); // Set the effect to be infinite
  ledManager.pushLEDEffect(effect); // Set the initial LED effect

  // Set up the gamemode manager after displays since it depends on the HUD
  gamemodeManager.init(this);

  soundPlayer.init(); // must be after side display init for some reason

  updateHUD(); // Update the HUD to show the initial state of the game

  soundPlayer.playSound(Sounds::arSound);
}


void LaserTag::loop() {
  // This gets called everytime the loop() function is called in the main.cpp / LaserTag.ino file

  soundPlayer.soundLoop(); // Check if any sounds need to be played / fill buffer
  Hardware::loop(); // Check if the gun needs to be turned off
  ledManager.loop(); // make sure neopixels are updated
  hudDisplay.loop(); // Call the HUD loop function
  buttons.pollButtons(); // Check the buttons for presses
  firing.FiringLoop(); // Call the firing loop function
  player.loop(); // Call the player loop function
  gamemodeManager.getCurrentGame()->loop(); // Call the current gamemode loop function
  networkManager.loop(); // Call the network loop function
  sideDisplay.getMenuManager()->loop(); // Call the menu manager loop function to refresh menus

  // turn off gun if no activity for a while
  if (millis() - buttons.getLastActivity() > MINS_TO_SLEEP * 60 * 1000) {
    turnOff();
  }
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
  return getGamemode()->canTakeDamage(shooterUnitnum) && player.canTakeDamage(shooterUnitnum) &&
         sideDisplay.getMenuManager()->getCurrentMenu()->getCanTakeDamage();
}

void LaserTag::turnOff() {
  // Turns off the gun with the latch circuit
  Logger::log(Logger::LogLevel::INFO, "Turning off");

  // We need to disconnect from the network before turning off the gun
  // wait a few secs to make sure the network disconnects before actually shutting it down.
  networkManager.disconnectNetwork();
  Hardware::turnOffSystem();

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

Networks::Network *LaserTag::getNetworkManager() {
  return &networkManager;
}

GamemodeManager *LaserTag::getGamemodeManager() {
  return &gamemodeManager;
}

Firing *LaserTag::getFiring() {
  return &firing;
}

Commands::CommandManager *LaserTag::getCommandManager() {
  return &commandManager;
}

SideDisplay *LaserTag::getSideDisplay() {
  return &sideDisplay;
}
