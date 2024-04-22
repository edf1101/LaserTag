/*
 * Created by Ed Fillingham on 21/04/2024.
 *
 * This menu is used to show all the game messages on the side display.
*/

#include "MessageMenu.h"
#include "MenuManager.h"
#include "../SideDisplay.h"
#include "../../../LaserTag.h"

namespace Menus {
    MessageMenu::MessageMenu(MenuManager *menuManager) {
      // constructor for the MessageMenu class
      this->menuManager = menuManager;
    }

    void MessageMenu::init(SideDisplay *_sideDisplay, Menu *parentMenu) {
      // This initialises the menu

      this->parentMenu = parentMenu;

      Menu::init(_sideDisplay);

      // get the message list and time list
      timeList = LaserTag::getNetworkManager()->getMessageQueue()->getMessageTimes();
      messageList = LaserTag::getNetworkManager()->getMessageQueue()->getMessages();

      // set the rotary counter max
      int rotaryMax = ((int) timeList->size() + 1) - 4;

      Serial.println(rotaryMax);
      setRotaryMax(rotaryMax);

      titleWidget.init(sideDisplay); // initialise the title widget

      // create and initialise all the message widgets
      for (int i = 0; i < 5; i++) {
        SideWidgets::SideWidgetText messageWidget = SideWidgets::SideWidgetText(23 + (i * 21), 2, "", 1,
                                                                                (i == 0) ? ST7735_WHITE : ST7735_RED);
        SideWidgets::SideWidgetText messageWidget2 = SideWidgets::SideWidgetText(33 + (i * 21), 2, "", 1,
                                                                                 (i == 0) ? ST7735_WHITE : ST7735_RED);
        messageWidget.init(sideDisplay);
        messageWidget2.init(sideDisplay);

        messageWidgets.emplace_back(messageWidget);
        messageWidgets.emplace_back(messageWidget2);
      }
      onRotaryTurned(0); // to update the messages
    }

    void MessageMenu::display(bool force) {
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


      for (auto &messageWidget: messageWidgets) {
        messageWidget.draw(force); // draw all the message widgets
      }
    }

    void MessageMenu::onRotaryTurned(int change) {
      // called when the rotary encoder is turned. Mainly used to scroll the messages

      // Do our own rotary counter logic, as we don't want it to roll over
      rotaryCounter += change;
      if (rotaryCounter < 0) rotaryCounter = 0;
      if (rotaryCounter > maxRotaryCounter - 1) rotaryCounter = maxRotaryCounter - 1;

      for (int i = 0; i < 5; i++) {
        int index = rotaryCounter + i;

        if (index == 0) {
          messageWidgets[0].setText("Return to menu");
          messageWidgets[1].setText("");
        } else {

          // This bit just formats the message so it has the time in front and is split over two lines
          std::string message = (*messageList)[index - 1];
          unsigned int time = (millis() - (*timeList)[index - 1]) / 1000;
          std::string timeString = time < 60 ? std::to_string(time) + "s: " : std::to_string(time / 60) + "m: ";
          std::string msg1 = timeString + message.substr(0, min(20, (int) message.size()));
          std::string msg2 = (message.size() > 20) ?  std::string(timeString.length()-1,' ') + message.substr(min(15, (int) message.size())) : "";

          // put the new strings onto the text widgets
          messageWidgets[i * 2].setText(msg1);
          messageWidgets[i * 2 + 1].setText(msg2);
        }
      }

    }

    void MessageMenu::onRotaryPressed() {
      // called when the rotary button is pressed
      // check if we are on the return button - if so return

      if (rotaryCounter == 0) {
        menuManager->switchMenu(parentMenu);
      }
    }


} // Menus