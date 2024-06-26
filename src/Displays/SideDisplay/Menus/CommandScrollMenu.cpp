/*
 * Created by Ed Fillingham on 29/04/2024.
 *
 * This menu is used to show commands in a menu on the side display.
*/

#include "CommandScrollMenu.h"
#include "MenuManager.h"
#include "../SideDisplay.h"
#include "LaserTag.h"

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
      for (auto &command : this->commandLists) {
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
                                                                             (i == 0) ? ST7735_WHITE : ST7735_RED);
        SideWidgets::SideWidgetText itemWidget2 = SideWidgets::SideWidgetText(33 + (i * 21), 2, "", 1,
                                                                              (i == 0) ? ST7735_WHITE : ST7735_RED);
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
          display->drawRect(0, 21 + (i * 21), 160, 22, ST7735_RED);
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

      for (int i = 0; i < min(5, (int) commandNames.size()); i++) {

        int index = 0;
        if (rotaryCounter >= commandNames.size() - 4) {
          index = (int) commandNames.size() - 4 + i;

          // update highlight
          for (int j = 0; j < 5; j++) {
            commandTextWidgets[j * 2].setColour(ST7735_RED);
            commandTextWidgets[j * 2 + 1].setColour(ST7735_RED);
          }
          int highlightIndex = rotaryCounter - (int) commandNames.size() + 4;

          commandTextWidgets[highlightIndex * 2].setColour(ST7735_WHITE);
          commandTextWidgets[highlightIndex * 2 + 1].setColour(ST7735_WHITE);

        } else {
          index = rotaryCounter + i;

          // update highlight
          for (int j = 1; j < 5; j++) {
            commandTextWidgets[j * 2].setColour(ST7735_RED);
            commandTextWidgets[j * 2 + 1].setColour(ST7735_RED);
          }
          commandTextWidgets[0].setColour(ST7735_WHITE);
          commandTextWidgets[1].setColour(ST7735_WHITE);
        }

        if (index == 0) {
          commandTextWidgets[0].setText("Return to menu");
          commandTextWidgets[1].setText("");
        } else {

          if (index > commandNames.size()) { // If it's out of range then just clear the text
            commandTextWidgets[i * 2].setText("");
            commandTextWidgets[i * 2 + 1].setText("");
            continue;
          }

          // This bit just formats the message, so it has the time in front and is split over two lines
          std::string message = commandNames[index - 1];

          std::string msg1 = message.substr(0, min(20, (int) message.size()));
          std::string msg2 = (message.size() > 20) ? message.substr(min(15, (int) message.size())) : "";

          // put the new strings onto the text widgets
          commandTextWidgets[i * 2].setText(msg1);
          commandTextWidgets[i * 2 + 1].setText(msg2);
        }
      }

    }

    void CommandScrollMenu::onRotaryPressed() {
      // called when the rotary button is pressed


      if (rotaryCounter == 0) { // check if we are on the return button
        menuManager->switchMenu(parentMenu);
      } else { // otherwise call the callback function

        Command* commandPressed = this->commandLists[rotaryCounter -1];
        LaserTag::getCommandManager()->sendCommand(commandPressed);
      }
    }


} // Menus