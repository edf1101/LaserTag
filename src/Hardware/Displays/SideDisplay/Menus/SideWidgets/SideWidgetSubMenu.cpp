/*
 * Created by Ed Fillingham on 19/04/2024.
*/

#include "SideWidgetSubMenu.h"
#include "../MenuManager.h"
#include <functional>
#include <utility>

namespace SideWidgets {

    SideWidgetSubMenu::SideWidgetSubMenu(int xStart, int yStart) : SideWidget(xStart, yStart) {
      // Constructor for the class

      width = 32;
      height = 128;
    }

    void SideWidgetSubMenu::draw(bool force) {
      // Draw the sub menu

      downButton.draw(force);
      upButton.draw(force);
      selectButton.draw(force);
      returnButton.draw(force);
    }

    void SideWidgetSubMenu::onRotaryTurned(int newValue) {
      rotaryCounter = newValue;

      // Set the new highlight state
      downButton.setHighlighted(false);
      upButton.setHighlighted(false);
      selectButton.setHighlighted(false);
      returnButton.setHighlighted(false);
      SideWidgetFunctionSelect *selectedButton = nullptr;
      if (rotaryCounter == 0) {
        selectedButton = &upButton;
      } else if (rotaryCounter == 1) {
        selectedButton = &downButton;
      } else if (rotaryCounter == 2) {
        selectedButton = &selectButton;
      } else if (rotaryCounter == 3) {
        selectedButton = &returnButton;
      }

      selectedButton->setHighlighted(true);
    }

    void SideWidgetSubMenu::onRotaryPressed() {
      // When the rotary encoder is pressed get the highlighted button's function
      SideWidgetFunctionSelect *selectedButton = nullptr;
      if (rotaryCounter == 0) {
        selectedButton = &upButton;
      } else if (rotaryCounter == 1) {
        selectedButton = &downButton;
      } else if (rotaryCounter == 2) {
        selectedButton = &selectButton;
      } else if (rotaryCounter == 3) {
        selectedButton = &returnButton;
      }
      std::function<void(void)> buttonFunc = *selectedButton->getFunction();
      buttonFunc();

    }

    void SideWidgetSubMenu::init(SideDisplay *sideDisplay, MenuManager *menuManager, Menus::Menu *prevMenu) {
      // Initialise the widget
      this->menuManager = menuManager;
      this->previousMenu = prevMenu;

      SideWidget::init(sideDisplay);

      upButton.init(sideDisplay);
      upButton.setFunction(std::bind(&SideWidgetSubMenu::increaseSubMenuCounter, this));

      downButton.init(sideDisplay);
      downButton.setFunction(std::bind(&SideWidgetSubMenu::decreaseSubMenuCounter, this));

      selectButton.init(sideDisplay);
      selectButton.setFunction(std::bind(&SideWidgetSubMenu::selectOption, this));

      returnButton.init(sideDisplay);
      returnButton.setFunction(std::bind(&SideWidgetSubMenu::returnToParent, this));

      upButton.setHighlighted(true); // start button should be highlighted
    }

    void SideWidgetSubMenu::increaseSubMenuCounter() {
      // Increase the sub menu counter
      subMenuCounter++;
      if (subMenuCounter > maxSubMenuCounter) {
        subMenuCounter = 0;
      }
      Logger::log(Logger::LogLevel::DETAIL, "Sub menu counter now: " + std::to_string(subMenuCounter));
      if (changeCallbackSet) {
        onChangeSubMenuCounter(subMenuCounter);
      }
    }

    void SideWidgetSubMenu::decreaseSubMenuCounter() {
      // decrease the sub menu counter
      subMenuCounter--;
      if (subMenuCounter < 0) {
        subMenuCounter = maxSubMenuCounter;
      }
      Logger::log(Logger::LogLevel::DETAIL, "Sub menu counter now: " + std::to_string(subMenuCounter));

      if (changeCallbackSet) {
        onChangeSubMenuCounter(subMenuCounter);
      }
    }

    void SideWidgetSubMenu::selectOption() {
      // Select the option

      if (pressCallbackSet) {
        onPressSubMenuCounter(subMenuCounter);
      }
    }

    void SideWidgetSubMenu::returnToParent() {
      // Return to the parent menu

      menuManager->switchMenu(previousMenu);
    }

    void SideWidgetSubMenu::reset() {
      // reset the sub menu

      subMenuCounter = 0; // reset the sub menu counter
      rotaryCounter = 0;
      // reset the state of the buttons
      upButton.setHighlighted(true);
      downButton.setHighlighted(false);
      selectButton.setHighlighted(false);
      returnButton.setHighlighted(false);

    }

    void SideWidgetSubMenu::setMaxSubMenuCounter(int maxSubMenuCounter) {
      // Set the maximum for the sub menu counter
      this->maxSubMenuCounter = maxSubMenuCounter;

      if (subMenuCounter > maxSubMenuCounter) { // reset counter if it is greater than the new max
        subMenuCounter = 0;
        if (changeCallbackSet) {
          onChangeSubMenuCounter(subMenuCounter);
        }
      }
    }

    void SideWidgetSubMenu::setCounterChangedCallback(std::function<void(int)> callback) {
      // Setter for the callback function related to the sub menu counter
      onChangeSubMenuCounter = std::move(callback);
      changeCallbackSet = true;
    }

    void SideWidgetSubMenu::setCounterPressedCallback(std::function<void(int)> callback) {
      // Setter for the callback function related to the sub menu counter being pressed
      onPressSubMenuCounter = std::move(callback);
      pressCallbackSet = true;
    }

} // SideWidgets