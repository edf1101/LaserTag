/*
 * Created by Ed Fillingham on 21/04/2024.
 *
 * This menu is used to show all the game messages on the side display.
*/

#ifndef LASERTAG_MESSAGEMENU_H
#define LASERTAG_MESSAGEMENU_H

#include "Menu.h"
#include <vector>
#include <string>
#include "Arduino.h"
#include "SideWidgets/SideWidgetText.h"
#include "../../../Network/MessageQueue.h"

class MenuManager; // forward declaration

namespace Menus {

    class MessageMenu : public Menu {
    public:
        explicit MessageMenu(MenuManager *menuManager); // constructor for the MessageMenu class

        void init(SideDisplay *_sideDisplay, Menu *parentMenu, Networks::MessageQueue *myQueue,
                  std::string title); // This initialises the menu

        void display(bool force); // display the new menu

        void onRotaryTurned(int change); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

    private:
        MenuManager *menuManager; // pointer to the menu manager
        Menu *parentMenu; // pointer to the parent menu

        Networks::MessageQueue *myQueue; // pointer to the message queue

        std::vector<std::string> *messageList; // a list of messages
        std::vector<unsigned long> *timeList; // a list of times

        SideWidgets::SideWidgetText titleWidget = SideWidgets::SideWidgetText(0, 2, "", 2,
                                                                              TFT_PRIMARY_COLOUR); // the title widget

        std::vector<SideWidgets::SideWidgetText> messageWidgets; // a list of the message widgets
    };

} // Menus

#endif //LASERTAG_MESSAGEMENU_H
