/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This menu represents the screen where you can select a sub menu to navigate to.
*/

#ifndef LASERTAG_SELECTPAGEMENU_H
#define LASERTAG_SELECTPAGEMENU_H

#include <vector>
#include <string>
#include "Arduino.h"
#include "Menu.h"
#include "../../config.h"
#include "SideWidgets/SideWidgetMenuSelect.h"
#include "SideWidgets/SideWidgetText.h"

class MenuManager;

namespace Menus {

    class SelectPageMenu : public Menu {
    public:
        SelectPageMenu(MenuManager* menuManager, std::string title); // constructor for the SelectPageMenu class
        void init(SideDisplay *_sideDisplay); // This initialises the menu

        void display(bool force); // display the new menu

        void onRotaryTurned(int change); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

        void addSubMenu(std::string name, Images::ImageData image, Menu *menu); // add a new sub menu widget

    private:
        MenuManager* menuManager; // pointer to the menu manager

        std::vector<SideWidgets::SideWidgetMenuSelect> menuWidgets; // a list of the submenu tile widgets
        SideWidgets::SideWidgetText titleWidget; // Widget to show the title
    };

} // Menus

#endif //LASERTAG_SELECTPAGEMENU_H
