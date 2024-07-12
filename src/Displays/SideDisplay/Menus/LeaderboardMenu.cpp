/*
 * Created by Ed Fillingham on 08/07/2024.
 *
 * This is a leaderboard that gets displayed on the side display. It shows stats etc about different players.
*/

#include "LeaderboardMenu.h"
#include "MenuManager.h"
#include "../../../LaserTag.h"
#include <set>

namespace Menus {

    LeaderboardMenu::LeaderboardMenu(MenuManager *menuManager) {
      // constructor for the MessageMenu class

      this->menuManager = menuManager;
    }

    void LeaderboardMenu::init(SideDisplay *_sideDisplay, Menu *parentMenu) {
      // This initialises the menu

      this->parentMenu = parentMenu;
      Menu::init(_sideDisplay);

      updatePlayersList();

      titleWidget.init(sideDisplay); // initialise the title widget
      returnTextWidget.init(sideDisplay); // initialise the return text widget

      // Create the player info widgets
      for (int i = 0; i < 5; i++) {
        playerInfoWidgets.emplace_back(21 + (i * 21));
        playerInfoWidgets[i].init(sideDisplay);
        playerInfoWidgets[i].setStatus();
      }

    }


    void LeaderboardMenu::updatePlayersList() {
      // This function updates the players list

      std::set<uint32_t> activeIds = LaserTag::getNetworkManager()->getActivePlayers();

      players.clear(); // clear the list of players

      // We'll sort the players by score
      // Since it's a small list, and we are doing it into a vector, we can use a selection sort.

      set<uint32_t> sortedIds; // holds the ids that have been sorted.
      for (int i = 0; i < activeIds.size(); i++) {
        uint32_t maxId = 0;
        int maxScore = -1;

        for (auto id: activeIds) { // find the player with the highest score

          if (sortedIds.find(id) != sortedIds.end()) { // If this id has already been sorted ignore it
            continue;
          }

          // get player score
          int revives = LaserTag::getNetworkManager()->getPlayerInMap(id)->revives;
          int health = LaserTag::getNetworkManager()->getPlayerInMap(id)->health;
          int score = revives * 100 + health; // score is a combination of revives and health

          if (score > maxScore) {
            maxScore = score;
            maxId = id;
          }
        }
        sortedIds.insert(maxId); // add the id to the sorted list
        players.emplace_back(LaserTag::getNetworkManager()->getPlayerInMap(maxId)); // add the player to the list
      }

      // List is now sorted so highest scores are at the top.
      setRotaryMax((int) players.size() + 1); // + 1 for return to menu bit.
    }

    void LeaderboardMenu::display(bool force) {
      // display the new menu

      if (force) {
        // get the raw display
        Adafruit_ST7735 *display = sideDisplay->getRawDisplay();
        for (int i = 0; i < 5; i++) {
          display->drawRect(0, 21 + (i * 21), 160, 22, TFT_SECONDARY_COLOUR);
        }
      }

      // Draw the player info widgets
      for (auto &playerInfoWidget: playerInfoWidgets) {
        playerInfoWidget.draw(force);
      }

      titleWidget.draw(force); // draw the title widget
      returnTextWidget.draw(false); // draw the return text widget
      // enable/ disable the return button & top PlayerInfoWidget. This should be done last

      bool returnButtonShowing = rotaryCounter <= 4;
      if (returnButtonShowing && force) {
        lastReturnButtonShowing = true;
        playerInfoWidgets[0].setStatus();
        playerInfoWidgets[0].draw(true);
        returnTextWidget.setText("Return to menu");
        returnTextWidget.draw(true);

      } else if (!returnButtonShowing && force) {
        lastReturnButtonShowing = false;
        returnTextWidget.setText("");
        returnTextWidget.draw(true);
        playerInfoWidgets[0].setStatus(players[0], 0);
        playerInfoWidgets[0].draw(true);
      }

    }

    void LeaderboardMenu::onRotaryTurned(int change) {
      // This gets called when the rotary encoder is turned. We use it to scroll through the players
      // Do this in case of any new players

      updatePlayersList();
      setRotaryMax((int) players.size() + 1); // + 1 for return to menu bit.

      // Do our own rotary counter logic, as we don't want it to roll over
      rotaryCounter += change;
      if (rotaryCounter < 0) rotaryCounter = 0;
      if (rotaryCounter > maxRotaryCounter-1) rotaryCounter = maxRotaryCounter-1;

      bool returnButtonShowing = rotaryCounter <= 4;
      returnTextWidget.setColour(rotaryCounter == 0 ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR);

      // set the highlight of all the player info widgets to false
      for (auto &playerInfoWidget: playerInfoWidgets) {
        playerInfoWidget.setHighlight(false);
      }
      if (rotaryCounter >= 4) {
        playerInfoWidgets[4].setHighlight(true);
      } else {
        playerInfoWidgets[rotaryCounter].setHighlight(true);
      }

      int startRow = returnButtonShowing ? 1 : 0;

      for (int displayRow = startRow; displayRow < 5 ; displayRow++) {
        int index = displayRow - startRow;
        int playerIndex = returnButtonShowing ?  index : rotaryCounter - 5 + index;

        if (playerIndex < players.size()){
          playerInfoWidgets[displayRow].setStatus(players[playerIndex], playerIndex);
        } else {
          playerInfoWidgets[displayRow].setStatus();
        }


      }

      // enable/ disable the return button & top PlayerInfoWidget. This should be done last
      if (returnButtonShowing && lastReturnButtonShowing == false) {
        lastReturnButtonShowing = true;
        playerInfoWidgets[0].setStatus();
        playerInfoWidgets[0].draw(true);
        returnTextWidget.setText("Return to menu");
        returnTextWidget.draw(true);

      } else if (!returnButtonShowing && lastReturnButtonShowing == true) {
        lastReturnButtonShowing = false;
        returnTextWidget.setText("");
        returnTextWidget.draw(true);
        playerInfoWidgets[0].setStatus(players[0], 0);
        playerInfoWidgets[0].draw(true);
      }


      display(false); // display the menu
    }

    void LeaderboardMenu::onRotaryPressed() {
      // called when the rotary button is pressed
      // check if we are on the return button - if so return

      if (rotaryCounter == 0) {
        menuManager->switchMenu(parentMenu);
      }
    }

    void LeaderboardMenu::resetMenu() {
      // extra onRotaryTurned to make sure the top bit is layed out correctly when you go into a menu

      rotaryCounter = 0;
      lastReturnButtonShowing = false;
      Serial.println("RESET MENU");
      onRotaryTurned(0);
    }


} // Menus