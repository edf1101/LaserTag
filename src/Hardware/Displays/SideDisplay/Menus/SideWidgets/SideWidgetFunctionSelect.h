/*
 * Created by Ed Fillingham on 16/04/2024.
 *
 * This class is a widget that when you press it, it runs a function
*/

#ifndef LASERTAG_SIDEWIDGETFUNCTIONSELECT_H
#define LASERTAG_SIDEWIDGETFUNCTIONSELECT_H

#include "Arduino.h"
#include "SideWidgetSelector.h"
#include <functional>


namespace SideWidgets {

    class SideWidgetFunctionSelect : public SideWidgetSelector {
    public:
        SideWidgetFunctionSelect(int yStart, int xStart,
                                 std::string name, Images::ImageData image,
                                 bool small = false); // Constructor for the class


        void setFunction(std::function<void(void)> function); // Set the function that this widget is associated with
        void draw(bool force); // Draw the widget to the screen

        std::function<void(void)> *getFunction(); // Get the function that this widget is associated with
        bool hasFunctionPointer(); // Whether the widget has a function associated with it
    private:
        Images::ImageData icon; // The icon to display next to the menu item must be 36px wide 31px tall
        std::string name; // The name of the menu item

        std::function<void(void)> function; // The menu that this widget is associated with
        bool hasFunction = false; // Whether the widget has a function associated with it

        bool small = false; // Whether the widget is small or not
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGETFUNCTIONSELECT_H
