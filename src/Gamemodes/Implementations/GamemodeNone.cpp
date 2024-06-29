/*
 * Created by Ed Fillingham on 13/04/2024.
 *
 * This gamemode represents when no gamemode is selected. It is the default gamemode.
*/

#include "GamemodeNone.h"
#include "../../LaserTag.h"

namespace Gamemodes {
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

      if (!LaserTag::getNetworkManager()->getInLobby()) {
        infoWidget.setTexts("Gun", "No Lobby");
      } else {
        infoWidget.setTexts("Game", "Not chosen");
      }

      infoWidget.draw(false);

      displayHud->getDisplay()->display();
    }

    bool GamemodeNone::canFire() {
      return false;
    }

    void GamemodeNone::initialisePlayer() {
      // Do nothing
    }

    bool GamemodeNone::canTakeDamage(int shooterUnitnum) {
      // Can't take damage in this gamemode as it's not a game
      return false;
    }

    Player GamemodeNone::getPlayerTemplate() {
      // This template is used to reset the players to a default state when it enters a new gamemode

      Player playerTemplate = {
              .unitnum = -1, // irrelevant as this field doesn't copy from the template
              .team = 0,// irrelevant as this field doesn't copy from the template
              .name = "Player",// irrelevant as this field doesn't copy from the template
              .revives = 0,
              .health = 0,
              .kills = 0,
              .carryingFlag = false,
              .gunIndex = 0 // 0 should be default gun (AR)
      };
      return playerTemplate;
    }

}