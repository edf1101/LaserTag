/*
 * Created by Ed Fillingham on 13/04/2024.
*/

#ifndef LASERTAG_HUDWIDGETBACKDROP_H
#define LASERTAG_HUDWIDGETBACKDROP_H

#include "HudWidget.h"
#include "../../ImageData.h"

namespace HudWidgets {

    class HudWidgetBackdrop : public HudWidget {
    public:
        HudWidgetBackdrop(int yStart, Images::ImageData background); // Constructor for the class (as base class just set the display)

        void draw(bool force); // Draw the widget to the screen

        void setBackground(Images::ImageData background); // Set the background image of the widget

    private:
        Images::ImageData background; // The image to display
    };

} // HudWidgets

#endif //LASERTAG_HUDWIDGETBACKDROP_H
