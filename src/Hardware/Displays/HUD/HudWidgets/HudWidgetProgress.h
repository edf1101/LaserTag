/*
 * Created by Ed Fillingham on 13/04/2024.
 *
 * This widget is a small progress bar (horizontal) that can be displayed on the HUD.
 * Used for things like health bars, loading bars etc.
*/

#ifndef LASERTAG_HUDWIDGETPROGRESS_H
#define LASERTAG_HUDWIDGETPROGRESS_H

#include "HudWidget.h"

namespace HudWidgets {

    class HudWidgetProgress : public HudWidget{
    public:
        // Constructor for the class (as base class just set the display)
        explicit HudWidgetProgress(int yCoordinate) : HudWidget(yCoordinate) {} ;

        void setProgress(int _progress); // Set the progress of the widget

        void draw(bool force); // Draw the widget to the screen

        void erase(); // Overwrite the erase function to do nothing

    private:
        int barWidth = 50; // The width of the progress bar
        int barHeight = 12; // The height of the progress bar

        int progress = 0; // The progress of the widget (0-100)

        int lastProgress = -1091001; // The last progress value we displayed (set something it will never be on start)
    };

} // HudWidgets

#endif //LASERTAG_HUDWIDGETPROGRESS_H
