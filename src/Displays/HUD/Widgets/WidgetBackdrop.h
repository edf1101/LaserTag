/*
 * Created by Ed Fillingham on 13/04/2024.
*/

#ifndef LASERTAG_WIDGETBACKDROP_H
#define LASERTAG_WIDGETBACKDROP_H

#include "HudWidget.h"
#include "../../ImageData.h"

namespace Widgets {

    class WidgetBackdrop : public HudWidget {
    public:
        WidgetBackdrop(int yStart, Images::ImageData background); // Constructor for the class (as base class just set the display)

        void draw(bool force); // Draw the widget to the screen

        void setBackground(Images::ImageData background); // Set the background image of the widget

    private:
        Images::ImageData background; // The image to display
    };

} // Widgets

#endif //LASERTAG_WIDGETBACKDROP_H
