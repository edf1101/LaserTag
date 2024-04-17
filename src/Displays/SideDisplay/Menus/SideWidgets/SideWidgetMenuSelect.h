/*
 * Created by Ed Fillingham on 16/04/2024.
*/

#ifndef LASERTAG_SIDEWIDGETMENUSELECT_H
#define LASERTAG_SIDEWIDGETMENUSELECT_H

#include "Arduino.h"
#include "SideWidget.h"


namespace SideWidgets {

    class SideWidgetMenuSelect : public SideWidget {
    public:
        SideWidgetMenuSelect(int yStart, int xStart,
                             std::string name, Images::ImageData image); // Constructor for the class

        void setHighlighted(bool highlighted); // Set the highlighted state of the widget
        void setMenu(Menus::Menu *menu); // Set the menu that this widget is associated with
        void draw(bool force); // Draw the widget to the screen

        Menus::Menu *getMenu(); // Get the menu that this widget is associated with
        bool hasMenuPointer(); // Whether the widget has a menu associated with it
    private:
        Images::ImageData icon; // The icon to display next to the menu item must be 36px wide 31px tall
        std::string name; // The name of the menu item

        Menus::Menu *menu; // The menu that this widget is associated with
        bool hasMenu = false; // Whether the widget has a menu associated with it

        // Highlighted state of the widget
        bool highlighted = false; // Whether the widget is currently highlighted
        bool lastHighlighted = false; // Whether the widget was highlighted last time it was drawn
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGETMENUSELECT_H
