/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This class represents a basic side widget.
*/

#ifndef LASERTAG_SIDEWIDGET_H
#define LASERTAG_SIDEWIDGET_H

#include "Arduino.h"
#include "Adafruit_ST7735.h"
#include "../Menu.h"
#include "../../../ImageData.h"

class SideDisplay;

namespace SideWidgets {

    class SideWidget {
    public:
        SideWidget(int yStart, int xStart); // constructor for the class

        virtual void init(SideDisplay *sideDisplay);

        virtual void erase(); // Erase the widget from the screen
        virtual void draw(bool force) = 0; // Draw the widget to the screen
    protected:
        SideDisplay *myDisplay; // Reference to the display object
        bool displayAssigned = false;

        // The starting y and x coordinates of the widget on the screen (top left corner)
        int yStart;
        int xStart;
        // The width and height of the widget on the screen
        int width = 0;
        int height = 0;
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGET_H
