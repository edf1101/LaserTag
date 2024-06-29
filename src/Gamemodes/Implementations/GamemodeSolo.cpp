/*
 * Created by Ed Fillingham on 12/04/2024.
*/

#include "GamemodeSolo.h"

namespace Gamemodes {
    GamemodeSolo::GamemodeSolo(LaserTag *_mySystem) : Gamemode(_mySystem) {
      name = "Solo Deathmatch";
      teamBased = false;
      playerStartingRevives = 3;

      // initialise widgets
      displayHud->getDisplay()->clearDisplay(); // clear the display

      backdropWidget.init(displayHud);
      progressWidget.init(displayHud);
      infoBoxWidget.init(displayHud);
      revivesWidget.init(displayHud, std::bind(&PlayerWrapper::getRevives, myPlayer));
      healthWidget.init(displayHud, std::bind(&PlayerWrapper::getHealth, myPlayer));
      ammoWidget.init(displayHud, std::bind(&Weapons::Gun::getAmmoRemaining, myPlayer->getGun()));
      magsWidget.init(displayHud, std::bind(&Weapons::Gun::getMagsRemaining, myPlayer->getGun()));

      changeHudState(HUD_PAUSED);

    }

    void GamemodeSolo::loop() {
      Gamemode::loop();
      if (currentState == HUD_REVIVING) {
        if (millis() - lastReviveHUDUpdate > 200) {
          lastReviveHUDUpdate = millis();
          progressWidget.setProgress((int) (myPlayer->getRespawnStatus() * 100));
          drawHUD();
        }

        if (myPlayer->getRespawnStatus() == 0) {
          changeHudState(HUD_GAME);
          drawHUD();
        }
      }
    }

    void GamemodeSolo::onPlayerDeath() {
// when the player dies just switch to a revive screen
      if (myPlayer->getRevives() > 0) {
        changeHudState(HUD_REVIVING);
        drawHUD();
      }
    }


    void GamemodeSolo::changeHudState(GamemodeSolo::hudStates newState) {

      // set the current state
      currentState = newState;

      // Erase all widgets
      backdropWidget.erase();
      progressWidget.erase();
      infoBoxWidget.erase();
      revivesWidget.erase();
      healthWidget.erase();
      ammoWidget.erase();
      magsWidget.erase();
      displayHud->getDisplay()->display(); // display the cleared display

      // set up new widgets with (force mode = true)
      switch (newState) {
        case HUD_PAUSED:
          infoBoxWidget.setLocation(0);
          infoBoxWidget.setTexts("Game", "Paused");
          infoBoxWidget.draw(true);
          break;
        case HUD_GAME:
          displayHud->setInfoStateCounts(2); // 2 states: display name, display gun
          infoBoxWidget.setLocation(0);

          if (!myPlayer->getGun()->getReloading()) {
            if (displayHud->getInfoStateCurrent() == 0) {
              infoBoxWidget.setTexts("Name", myPlayer->getName());
            } else if (displayHud->getInfoStateCurrent() == 1) {
              infoBoxWidget.setTexts("Gun", myPlayer->getGun()->getAcronym());
            }
          }
          else{
            infoBoxWidget.setTexts("Rload", myPlayer->getGun()->getReloadDescription());
          }
          infoBoxWidget.draw(true);
          revivesWidget.draw(true);
          healthWidget.draw(true);
          ammoWidget.draw(true);
          magsWidget.draw(true);
          break;
        case HUD_REVIVING:
          infoBoxWidget.setLocation(52);
          infoBoxWidget.setTexts("By", "Player1");
          progressWidget.setProgress(0);
          backdropWidget.draw(true);
          progressWidget.draw(true);
          infoBoxWidget.draw(true);
          break;
      }
      displayHud->getDisplay()->display(); // display the new widgets
    }

    void GamemodeSolo::drawHUD() {
      if (currentState == HUD_GAME) {
        if (!myPlayer->getGun()->getReloading()) {
          if (displayHud->getInfoStateCurrent() == 0) {
            infoBoxWidget.setTexts("Name", myPlayer->getName());
          } else if (displayHud->getInfoStateCurrent() == 1) {
            infoBoxWidget.setTexts("Gun", myPlayer->getGun()->getAcronym());
          }
        }
        else{
          infoBoxWidget.setTexts("Rload", myPlayer->getGun()->getReloadDescription());
        }
        infoBoxWidget.draw(false); // draw the info box (name and gun)
        revivesWidget.draw(false);
        healthWidget.draw(false);
        ammoWidget.draw(false);
        magsWidget.draw(false);
      } else if (currentState == HUD_REVIVING) {
        // don't draw the backdrop as it's already drawn behind and wont update
        progressWidget.draw(false);
        infoBoxWidget.draw(false);
      } else if (currentState == HUD_PAUSED) {
        infoBoxWidget.draw(false);
      }

      displayHud->getDisplay()->display(); // display the new widgets
    }

    void GamemodeSolo::setGamePauseState(bool pause) {
      // set the game pause state

      Gamemode::setGamePauseState(pause);
      if (pause) {
        changeHudState(HUD_PAUSED);
      } else {
        changeHudState(HUD_GAME);
      }
    }

    Player GamemodeSolo::getPlayerTemplate() {
      // This template is used to reset the players to a default state when it enters a new gamemode

      Player playerTemplate = {
              .unitnum = -1, // irrelevant as this field doesn't copy from the template
              .team = -1,// irrelevant as this field doesn't copy from the template
              .name = "Player",// irrelevant as this field doesn't copy from the template
              .revives = 3,
              .health = 100,
              .kills = 0,
              .carryingFlag = false,
              .gunIndex = 0 // 0 should be default gun (AR)
      };
      return playerTemplate;
    }

    void GamemodeSolo::loadGameDetails(JsonDocument gameDetails) {
      // recreate the details saved by getGameDetails() to load the game state
      started = gameDetails["started"];
      setGamePauseState(!started);
    }

    JsonDocument GamemodeSolo::getGameDetails() {
      // Return all important details about this gamemode so it can be recreated in loadGameDetails()

      JsonDocument gameDetails;
      gameDetails["started"] = started;

      return gameDetails;
    }

}