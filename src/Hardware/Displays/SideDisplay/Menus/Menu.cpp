/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * A menu is an place on the side screen where the user can interact with the system.
 * This is the base class for all menus.
*/

#include "Menu.h"
#include "../SideDisplay.h"

namespace Menus {
    Menu::Menu() {
      // constructor for the Menu class

    }

    void Menu::init(SideDisplay *_sideDisplay) {
      // initialise the menu
      sideDisplay = _sideDisplay;
    }

    void Menu::setRotaryMax(int max) {
      // set the maximum value for the rotary encoder
      maxRotaryCounter = max;
    }

    void Menu::onRotaryTurned(int change) {
      // called when the rotary encoder is turned
      rotaryCounter =
              (rotaryCounter + change + maxRotaryCounter) % maxRotaryCounter; // add the change to the rotary counter

      if (change != 0)
        Logger::log(Logger::LogLevel::DETAIL, "menu.h: Rotary Turned position now: " + std::to_string(rotaryCounter));

    }

    void Menu::onRotaryPressed() {
      // called when the button is pressed

      Logger::log(Logger::LogLevel::DETAIL, "menu.h: Rotary Pressed");
    }

    bool Menu::getCanTakeDamage() {
      // iterate through parents until get to root or somewhere that has admin required access.

      if (requiresAdmin)
        return false;

      if (hasParentMenu)
        return parentMenu->getCanTakeDamage();

      return true;

    }

    void Menu::setParentMenu(Menu *parent) {
      parentMenu = parent; // set the parent menu
      hasParentMenu = true; // whether the menu has a parent menu
    }

    void Menu::resetMenu() {
      rotaryCounter = 0;
    }

    void Menu::display(bool force) {

    }

    void Menu::erase() {
      // erase the whole screen of menu

      delay(5);
      Adafruit_ST7735 *rawDisplay = sideDisplay->getRawDisplay();
      delay(3);
      rawDisplay->fillScreen(ST7735_BLACK);
    }

    void Menu::setRequiresAdmin(bool _requiresAdmin) {
      // Setter for requires admin
      this->requiresAdmin = _requiresAdmin;
    }

    bool Menu::getRequiresAdmin() {
      // Getter for requires admin
      return this->requiresAdmin;
    }

} // Menus
