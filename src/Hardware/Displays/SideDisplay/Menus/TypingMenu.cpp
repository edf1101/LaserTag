/*
 * Created by Ed Fillingham on 22/04/2024.
*/

#include "TypingMenu.h"
#include "MenuManager.h"
#include "../SideDisplay.h"
#include <utility>

#define BACK_SYMBOL 0x11
#define SET_SYMBOL 0x1E

namespace Menus {
    TypingMenu::TypingMenu(MenuManager *menuManager, std::string title, const std::string &allChars, bool hideString)
            : titleWidget(2, 2, std::move(title), 2, TFT_PRIMARY_COLOUR),
              completeStringWidget(40, 20, "", 2, TFT_PRIMARY_COLOUR) {
      // constructor for the TypingMenu class


      this->hideCompleteString = hideString; // assign the hide string variable
      this->menuManager = menuManager; // assign the pointer to the menu manager

      for (char c: allChars) { // add all the characters to the character set
        characterSet.push_back(c);
      }

      setRotaryMax((int) characterSet.size() + 2); // set the maximum value for the rotary encoder
    }

    void TypingMenu::init(SideDisplay *_sideDisplay, Menu *parentMenu) {
      // initialise the menu

      this->prevMenu = parentMenu; // assign the pointer to the parent menu

      Menu::init(_sideDisplay);
      titleWidget.init(_sideDisplay);
      completeStringWidget.init(_sideDisplay);

      for (int i = 0; i < 5; i++) {  // create the character widgets and set them up

        uint16_t colour = (i == 2) ? TFT_SECONDARY_COLOUR : TFT_PRIMARY_COLOUR;
        char c;
        int index = (rotaryCounter + i + maxRotaryCounter - 2) % maxRotaryCounter;

        if (index < characterSet.size()) // draw the character set
          c = characterSet[index];
        else if (index == characterSet.size()) // draw the backspace character
          c = BACK_SYMBOL;
        else if (index == characterSet.size() + 1) // draw the set character
          c = SET_SYMBOL;


        SideWidgets::SideWidgetText characterWidget = SideWidgets::SideWidgetText(106, 12 + (30 * i),
                                                                                  std::string(1, c),
                                                                                  2,
                                                                                  colour);

        characterWidget.init(_sideDisplay);
        characterWidgets.push_back(characterWidget);
      }

    }

    void TypingMenu::display(bool force) {
      // display the menu

      if (force) { // draw the boxes
        Adafruit_ST7735 *rawDisplay = sideDisplay->getRawDisplay();

        int startPosX = 5;
        int startPosY = 100;

        for (int i = 0; i < 5; i++) {
          rawDisplay->drawRect((short) (startPosX + (30 * i)), (short) startPosY, 25, 25, TFT_PRIMARY_COLOUR);
        }

        rawDisplay->drawRect(-1, 37, 170, 20, TFT_PRIMARY_COLOUR);
      }

      titleWidget.draw(force);
      completeStringWidget.draw(force);

      for (int i = 0; i < 5; i++) { // draw the character widgets
        characterWidgets[i].draw(force);
      }

    }

    void TypingMenu::onRotaryTurned(int change) {
      // When its turned rotate through the character set

      Menu::onRotaryTurned(change);

      for (int i = 0; i < 5; i++) { // set the new text widgets
        int index = (rotaryCounter + i + maxRotaryCounter - 2) % maxRotaryCounter;

        if (index < characterSet.size()) // draw the character set
          characterWidgets[i].setText(std::string(1, characterSet[index]));
        else if (index == characterSet.size()) // draw the backspace character
          characterWidgets[i].setText(std::string(1, BACK_SYMBOL));
        else if (index == characterSet.size() + 1) // draw the set character
          characterWidgets[i].setText(std::string(1, SET_SYMBOL));
      }

      display(false);
    }

    void TypingMenu::onRotaryPressed() {
      // When the button is pressed, add the character to the string

      int index = (rotaryCounter + maxRotaryCounter) % (maxRotaryCounter); // get the current index
      char currentChar = characterSet[index]; // get the current character

      if (index == maxRotaryCounter - 1) { // Set the string
        Logger::log(Logger::LogLevel::DETAIL,"Set a new name");


        if (!completeString.empty() && setCallbackString) { // if its not empty do something with the string
          callback(completeString);
        }

        menuManager->switchMenu(prevMenu); // go back a menu

        return;

      } else if (index == maxRotaryCounter - 2) { // Backspace character

        if (!completeString.empty()) {
          completeString.pop_back();
          completeStringWidget.setText(hideCompleteString ? std::string(completeString.size(), '*') : completeString);
        }
        Logger::log(Logger::LogLevel::DETAIL,"Name menu backspace");

      } else { // add a character to the string

        completeString.push_back(currentChar);
        completeStringWidget.setText(hideCompleteString ? std::string(completeString.size(), '*') : completeString);
      }


    }

    void TypingMenu::resetMenu() {
      // reset the menu

      Menu::resetMenu();
      completeString = "";
      completeStringWidget.setText("");
      onRotaryTurned(0);

    }

    void TypingMenu::setCallback(std::function<void(std::string)> callback) {
      // set the callback function

      setCallbackString = true;
      this->callback = callback;
    }


} // Menus