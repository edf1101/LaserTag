/*
 * Created by Ed Fillingham on 21/04/2024.
 *
 * This menu is used to show all the game messages on the side display.
*/

#ifndef LASERTAG_COMMANDSCROLLMENU_H
#define LASERTAG_COMMANDSCROLLMENU_H

#include "Menu.h"
#include <vector>
#include <string>
#include <functional>
#include "Arduino.h"
#include "SideWidgets/SideWidgetText.h"
#include "../../../Commands/Command.h"

class MenuManager; // forward declaration
using namespace std;
namespace Menus {

    class CommandScrollMenu : public Menu {
    public:
        explicit CommandScrollMenu(MenuManager *menuManager); // constructor for the MessageMenu class

        void
        init(SideDisplay *_sideDisplay, Menu *parentMenu, string commandGroup); // This initialises the menu

        void display(bool force); // display the new menu

        void onRotaryTurned(int change); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

    private:
        MenuManager *menuManager; // pointer to the menu manager
        Menu *parentMenu; // pointer to the parent menu
        string commandGroup; // the group of commands to display
        vector<string> commandNames; // the list of command names
        vector<Commands::Command*> commandLists; // the list of command objects

        SideWidgets::SideWidgetText titleWidget = SideWidgets::SideWidgetText(0, 2, "", 2,
                                                                              ST7735_WHITE); // the title widget

        std::vector<SideWidgets::SideWidgetText> commandTextWidgets; // a list of the message widgets
    };

} // Menus

#endif //LASERTAG_COMMANDSCROLLMENU_H
