/*
 * Created by Ed Fillingham on 14/04/2024.
 *
 * This class abstracts the complexity of managing / switching gamemodes.
*/

#include "GamemodeManager.h"


GamemodeManager::GamemodeManager(LaserTag *laserTag) {
  // constructor for the gamemode manager
  mySystem = laserTag; // assign the pointer to the main system object


}

void GamemodeManager::init() {
  // Set the initial gamemode to none
  currentGamemode = new GamemodeSolo(mySystem);
}

Gamemode *GamemodeManager::getCurrentGame() {
  // Get the current gamemode

  return currentGamemode;
}

void GamemodeManager::switchGamemode(GamemodeManager::GamemodeOptions _option) {
  // clean up the current gamemode
  delete currentGamemode;

  // Switch the gamemode to the specified option
  switch (_option) {
    case NONE:
      currentGamemode = new GamemodeNone(mySystem);
      break;
    case SOLO:
      currentGamemode = new GamemodeSolo(mySystem);
      break;
  }

}




