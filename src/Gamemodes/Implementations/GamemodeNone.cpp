/*
 * Created by Ed Fillingham on 13/04/2024.
 *
 * This gamemode represents when no gamemode is selected. It is the default gamemode.
*/

#include "GamemodeNone.h"
#include "../../LaserTag.h"


GamemodeNone::GamemodeNone(LaserTag *_mySystem) : Gamemode(_mySystem) {
  // Set up gamemode level variables
  name = "None";
  teamBased = false;
  playerStartingRevives = 0;

  // init the widgets
  infoWidget.init(displayHud);

  // Start drawing the HUD
  displayHud->getDisplay()->clearDisplay(); // empty the display
  infoWidget.setTexts("Game", "Not chosen");
}

void GamemodeNone::setGamePauseState(bool paused) {
  // Do nothing
}

void GamemodeNone::drawHUD() {
  // always display no game message
  infoWidget.draw(false);

  displayHud->getDisplay()->display();
}

bool GamemodeNone::canFire() {
  return false;
}

void GamemodeNone::initialisePlayer() {
    // Do nothing
}