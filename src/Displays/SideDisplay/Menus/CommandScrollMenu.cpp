/*
 * Created by Ed Fillingham on 29/04/2024.
 *
 * This menu is used to show commands in a menu on the side display.
*/

#include "CommandScrollMenu.h"
#include "MenuManager.h"
#include "../SideDisplay.h"
#include "../../../LaserTag.h"

namespace Menus {

    using namespace Commands;

    CommandScrollMenu::CommandScrollMenu(MenuManager *menuManager) {
      // constructor for the MessageMenu class
      this->menuManager = menuManager;
    }

    void CommandScrollMenu::init(SideDisplay *_sideDisplay, Menu *parentMenu, string _commandGroup) {
      // This initialises the menu

      this->parentMenu = parentMenu;
      this->commandGroup = _commandGroup;

      Menu::init(_sideDisplay);

      // get the name for all the commands and put them in a list
      this->commandLists = Command::getCommandsByGroup(_commandGroup);
      for (auto &command: this->commandLists) {
        commandNames.push_back(command->getCommandName());
      }

      // set the rotary counter max
      int rotaryMax = ((int) commandNames.size() + 1);

      setRotaryMax(rotaryMax);

      titleWidget.init(sideDisplay); // initialise the title widget
      titleWidget.setText(_commandGroup); // set the title widget text

      // create and initialise all the message widgets
      for (int i = 0; i < 5; i++) {
        SideWidgets::SideWidgetText itemWidget = SideWidgets::SideWidgetText(23 + (i * 21), 2, "", 1,
                                                                             (i == 0) ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR);
        SideWidgets::SideWidgetText itemWidget2 = SideWidgets::SideWidgetText(33 + (i * 21), 2, "", 1,
                                                                              (i == 0) ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR);
        itemWidget.init(sideDisplay);
        itemWidget2.init(sideDisplay);
        commandTextWidgets.emplace_back(itemWidget);
        commandTextWidgets.emplace_back(itemWidget2);
      }
      onRotaryTurned(0); // to update the messages
    }

    void CommandScrollMenu::display(bool force) {
      // display the new menu

      titleWidget.draw(force); // draw the title widget
      // draw bounding boxes if force is true
      if (force) {
        // get the raw display
        Adafruit_ST7735 *display = sideDisplay->getRawDisplay();
        for (int i = 0; i < 5; i++) {
          display->drawRect(0, 21 + (i * 21), 160, 22, TFT_SECONDARY_COLOUR);
        }
      }


      for (auto &messageWidget: commandTextWidgets) {
        messageWidget.draw(force); // draw all the message widgets
      }
    }

    void CommandScrollMenu::onRotaryTurned(int change) {
      // called when the rotary encoder is turned. Mainly used to scroll the messages

      // Do our own rotary counter logic, as we don't want it to roll over
      rotaryCounter += change;
      if (rotaryCounter < 0) rotaryCounter = 0;
      if (rotaryCounter > maxRotaryCounter - 1) rotaryCounter = maxRotaryCounter - 1;

      int highlightedRow = min(rotaryCounter, 4); // which row to highlight white

      // set colour of all the widgets
      for(auto &commandTextWidget: commandTextWidgets) {
        commandTextWidget.setColour(TFT_SECONDARY_COLOUR);
      }
      // then set highlighted ones to white
      commandTextWidgets[highlightedRow * 2].setColour(TFT_PRIMARY_COLOUR);
      commandTextWidgets[highlightedRow * 2 + 1].setColour(TFT_PRIMARY_COLOUR);

      for (int row = 0; row < 5; row++) {

        // displayOnRow is which command to display on the row. -1 means we are on the return button else it is the command (as array index)
        int displayOnRow = ((rotaryCounter <= 4) ? row : row + (rotaryCounter - 4)) - 1;


        // now set the text
        if (displayOnRow == -1) {
          commandTextWidgets[row * 2].setText("Return to menu");
          commandTextWidgets[(row * 2) + 1].setText("");
        }
        else if (displayOnRow < (int) commandNames.size()) {
          commandTextWidgets[row * 2].setText(commandNames[displayOnRow]);
          commandTextWidgets[(row * 2) + 1].setText("");
        } else {
          commandTextWidgets[row * 2].setText("");
          commandTextWidgets[(row * 2) + 1].setText("");
        }

      }

    }

    void CommandScrollMenu::onRotaryPressed() {
      // called when the rotary button is pressed


      if (rotaryCounter == 0) { // check if we are on the return button
        menuManager->switchMenu(parentMenu);
      } else { // otherwise call the callback function

        Command *commandPressed = this->commandLists[rotaryCounter - 1];
        LaserTag::getCommandManager()->sendCommand(commandPressed);
      }
    }


} // Menus