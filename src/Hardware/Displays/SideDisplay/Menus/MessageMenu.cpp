/*
 * Created by Ed Fillingham on 21/04/2024.
 *
 * This menu is used to show all the game messages on the side display.
*/

#include "MessageMenu.h"

#include <utility>
#include "MenuManager.h"
#include "../SideDisplay.h"

namespace Menus {
    MessageMenu::MessageMenu(MenuManager *menuManager) {
      // constructor for the MessageMenu class
      this->menuManager = menuManager;
    }

    void MessageMenu::init(SideDisplay *_sideDisplay, Menu *parentMenu, Networks::MessageQueue *myQueue, std::string title) {
      // This initialises the menu

      this->parentMenu = parentMenu;
      this->myQueue = myQueue;
      Menu::init(_sideDisplay);

      // get the message list and time list
      timeList = myQueue->getMessageTimes();
      messageList = myQueue->getMessages();

      // set the rotary counter max
      int rotaryMax = ((int) timeList->size() + 1);

      setRotaryMax(rotaryMax);

      titleWidget.init(sideDisplay); // initialise the title widget
      titleWidget.setText(std::move(title)); // set the title widget text

      // create and initialise all the message widgets
      for (int i = 0; i < 5; i++) {
        SideWidgets::SideWidgetText messageWidget = SideWidgets::SideWidgetText(23 + (i * 21), 2, "", 1,
                                                                                (i == 0) ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR);
        SideWidgets::SideWidgetText messageWidget2 = SideWidgets::SideWidgetText(33 + (i * 21), 2, "", 1,
                                                                                 (i == 0) ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR);
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
          display->drawRect(0, 21 + (i * 21), 160, 22, TFT_SECONDARY_COLOUR);
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

      // deal with highlighted row

      int highlightedRow = min(rotaryCounter, 4); // which row to highlight white

      // set colour of all the widgets
      for(auto &widget: messageWidgets) {
        widget.setColour(TFT_SECONDARY_COLOUR);
      }
      // then set highlighted ones to white
      messageWidgets[highlightedRow * 2].setColour(TFT_PRIMARY_COLOUR);
      messageWidgets[highlightedRow * 2 + 1].setColour(TFT_PRIMARY_COLOUR);


      for (int row = 0; row < 5; row++) {

        // displayOnRow is which command to display on the row. -1 means we are on the return button else it is the command (as array index)
        int displayOnRow = ((rotaryCounter <= 4) ? row : row + (rotaryCounter - 4)) - 1;


        // now set the text
        if (displayOnRow == -1) {
          messageWidgets[row * 2].setText("Return to menu");
          messageWidgets[(row * 2) + 1].setText("");
        }
        else if (displayOnRow < (int) (*messageList).size()) {

          // This bit just formats the message so it has the time in front and is split over two lines
          std::string message = (*messageList)[displayOnRow ];
          unsigned int time = (millis() - (*timeList)[displayOnRow ]) / 1000;
          std::string timeString = time < 60 ? std::to_string(time) + "s: " : std::to_string(time / 60) + "m: ";
          std::string msg1 = timeString + message.substr(0, min(20, (int) message.size()));
          std::string msg2 = (message.size() > 20) ? std::string(timeString.length() - 1, ' ') +
                                                     message.substr(min(20, (int) message.size())) : "";

          // put the new strings onto the text widgets
          messageWidgets[row * 2].setText(msg1);
          messageWidgets[(row * 2) + 1].setText(msg2);

        } else {
          messageWidgets[row * 2].setText("");
          messageWidgets[(row * 2) + 1].setText("");
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