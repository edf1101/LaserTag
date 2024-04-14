/*
 * Created by Ed Fillingham on 12/04/2024.
*/

#include "GamemodeSolo.h"


GamemodeSolo::GamemodeSolo(LaserTag *_mySystem) : Gamemode(_mySystem) {
  name = "Solo Deathmatch";
  teamBased = false;
  playerStartingRevives = 3;

  // initialise widgets
  displayHud->getDisplay()->clearDisplay(); // clear the display

  backdropWidget.init(displayHud);
  progressWidget.init(displayHud);
  infoBoxWidget.init(displayHud);
  revivesWidget.init(displayHud, std::bind(&Player::getRevives, myPlayer));
  healthWidget.init(displayHud, std::bind(&Player::getHealth, myPlayer));
  ammoWidget.init(displayHud, std::bind(&Weapons::Gun::getAmmoRemaining, myPlayer->getGun()));
  magsWidget.init(displayHud, std::bind(&Weapons::Gun::getMagsRemaining, myPlayer->getGun()));

  changeHudState(HUD_PAUSED);

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
      if(displayHud->getInfoStateCurrent() == 0){
        infoBoxWidget.setTexts("Name", myPlayer->getName());
      } else if (displayHud->getInfoStateCurrent() == 1){
        infoBoxWidget.setTexts("Gun", myPlayer->getGun()->getAcronym());
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
      backdropWidget.draw(true);
      progressWidget.draw(true);
      infoBoxWidget.draw(true);
      break;
  }
  displayHud->getDisplay()->display(); // display the new widgets
}

void GamemodeSolo::drawHUD() {
  if (currentState == HUD_GAME) {
    if(displayHud->getInfoStateCurrent() == 0){
      infoBoxWidget.setTexts("Name", myPlayer->getName());
    } else if (displayHud->getInfoStateCurrent() == 1){
      infoBoxWidget.setTexts("Gun", myPlayer->getGun()->getAcronym());
    }
    infoBoxWidget.draw(false); // draw the info box (name and gun)
    revivesWidget.draw(false);
    healthWidget.draw(false);
    ammoWidget.draw(false);
    magsWidget.draw(false);
  } else if (currentState == HUD_REVIVING) {
    backdropWidget.draw(false);
    progressWidget.draw(false);
    infoBoxWidget.draw(false);
  } else if (currentState == HUD_PAUSED) {
    infoBoxWidget.draw(false);
  }

  displayHud->getDisplay()->display(); // display the new widgets
}

void GamemodeSolo::setGamePauseState(bool pause) {
  Gamemode::setGamePauseState(pause);
  if (pause) {
    changeHudState(HUD_PAUSED);
  } else {
    changeHudState(HUD_GAME);
  }
}
