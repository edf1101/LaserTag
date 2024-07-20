/*
 * Created by Ed on 13/04/2024.
 *
 * This class represents a basic HUD widget.
 * A HUD widget is a small part of the HUD that displays a specific piece of information.
 * It has smart behaviours to update itself when the information changes.
 *
 * This class is abstract and should not be instantiated.
*/

#ifndef LASERTAG_HUDWIDGET_H
#define LASERTAG_HUDWIDGET_H

#include <Arduino.h>
#include "../HudDisplay.h"

namespace HudWidgets {

    class HudWidget {
    public:
        HudWidget(int yStart); // Constructor for the class (as base class just set the display)

        ~HudWidget() { // destructor erases the widget when its destroyed
          erase();
        }; // Destructor for the class
        void init(HudDisplay *_disp);

        void setLocation(int y); // Set the location of the widget on the screen
        virtual void draw(bool force) = 0; // Draw the widget to the screen
        void erase(); // Erase the widget from the screen

    protected:
        HudDisplay *display; // Reference to the display object
        bool displayAssigned = false; // Whether the display has been assigned yet

        int yCoordinate; // The y coordinate of the widget on the screen
        int widgetHeight = 0; // The height of the widget on the screen (0 since this is an abstract class)
    };

}
#endif //LASERTAG_HUDWIDGET_H
