/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This widget is used to display Images on the side display.
*/

#ifndef LASERTAG_SIDEWIDGETIMAGE_H
#define LASERTAG_SIDEWIDGETIMAGE_H

#include <string>
#include "Arduino.h"
#include "SideWidget.h"

namespace SideWidgets {

    class SideWidgetImage : public SideWidget{
    public:
        SideWidgetImage(int yStart, int xStart, Images::ImageData image, uint16_t colour); // Constructor for the class
        void draw(bool force); // Draw the widget to the screen
        void setImage(Images::ImageData image); // Set the image to display
    private:
        Images::ImageData image; // The image to display
        Images::ImageData lastImage; // The last image displayed

        uint16_t colour; // The colour of the image
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGETIMAGE_H
