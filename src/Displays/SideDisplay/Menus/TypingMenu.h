/*
 * Created by Ed Fillingham on 22/04/2024.
 *
 * This class will handle the typing menu, where the user can type in a message and have the string passed to a callback.
 * Used for admin password entry and name entry.
*/

#ifndef LASERTAG_TYPINGMENU_H
#define LASERTAG_TYPINGMENU_H

#include <vector>
#include <string>
#include <functional>
#include "Menu.h"
#include "Arduino.h"
#include "SideWidgets/SideWidgetText.h"

class MenuManager; // forward declaration

namespace Menus {

    class TypingMenu : public Menu {
    public:
        TypingMenu(MenuManager* menuManager, std::string title ,const std::string& allChars, bool hideString = false); // constructor for the TypingMenu class

        void init(SideDisplay *_sideDisplay, Menu* parentMenu); // initialise the menu

        void display(bool force) override; // display the menu

        void onRotaryTurned(int change); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

        void resetMenu(); // reset the menu

        void setCallback(std::function<void(std::string)> callback); // set the callback function

    private:
        MenuManager* menuManager; // pointer to the menu manager
        Menu* prevMenu; // pointer to the previous menu

        std::vector<char> characterSet; // the set of characters that can be typed

        SideWidgets::SideWidgetText titleWidget; // the title widget

        std::string completeString; // the title of the menu
        SideWidgets::SideWidgetText completeStringWidget; // the title widget
        bool hideCompleteString = false; // whether to hide the complete string

        std::vector<SideWidgets::SideWidgetText> characterWidgets; // the character widgets

        std::function<void(std::string)> callback; // the callback function
        bool setCallbackString = false;
    };

} // Menus

#endif //LASERTAG_TYPINGMENU_H
