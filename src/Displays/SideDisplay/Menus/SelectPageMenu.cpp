/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This menu represents the screen where you can select a sub menu to navigate to.
*/

#include "SelectPageMenu.h"

#include <utility>
#include "Adafruit_ST7735.h"
#include "../SideDisplay.h"
#include "MenuManager.h"


namespace Menus {

    SelectPageMenu::SelectPageMenu(MenuManager *menuManager, std::string title)
            : titleWidget(SideWidgets::SideWidgetText(2, 2, std::move(title), 2, ST7735_WHITE)) {
      // constructor for the SelectPageMenu class

      this->menuManager = menuManager;
    }

    void SelectPageMenu::init(SideDisplay *_sideDisplay) {
      // This initialises the menu

      Menu::init(_sideDisplay);

      titleWidget.init(sideDisplay); // initialise the title widget
    }

    void SelectPageMenu::display(bool force) {
      // display the new menu
      titleWidget.draw(force);

      for (auto &menuWidget: menuWidgets) {
        menuWidget.draw(force);
      }
    }

    void SelectPageMenu::onRotaryTurned(int change) {
      // called when the rotary encoder is turned
      Menu::onRotaryTurned(change);

      // loop through all the menu widgets
      for (auto &menuWidget: menuWidgets) {
        menuWidget.setHighlighted(false); // set them all to not highlighted
      }

      // highlight the current menu widget
      menuWidgets[rotaryCounter].setHighlighted(true);
    }

    void SelectPageMenu::addSubMenu(std::string name, Images::ImageData image, Menu *menu) {
      // add a new sub menu to the list of sub menus

      // calculate its position on the screen

      int currentMenuCount = menuWidgets.size();
      int xCount = currentMenuCount % 3;
      int yCount = currentMenuCount / 3;

      int x = 5 + (xCount * 54);
      int y = 23 + (yCount * 55);

      // Create the instance of the new widget
      auto *newWidget = new SideWidgets::SideWidgetMenuSelect(y, x, name, image);
      newWidget->init(sideDisplay);
      if (currentMenuCount == 0) {
        newWidget->setHighlighted(true);
      }

      if (menu != nullptr) { // if the menu pointer is not null set the menu pointer
        newWidget->setMenu(menu);
      }

      menuWidgets.push_back(*newWidget); // put it in the list (vector technically)

      setRotaryMax(menuWidgets.size()); // update the rotary counter that there's a new menu
    }

    void SelectPageMenu::onRotaryPressed() {
      // called when the button is pressed

      Menu::onRotaryPressed();
      SideWidgets::SideWidgetMenuSelect *selectedWidget = &menuWidgets[rotaryCounter];

      if (!selectedWidget->hasMenuPointer()) { // if the selected widget doesn't have a menu pointer return
        return;
      }

      menuManager->switchMenu(selectedWidget->getMenu()); // set the menu to the selected widget's menu
    }
} // Menus