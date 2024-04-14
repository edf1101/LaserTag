/*
 * Created by Ed on 13/04/2024.
*/

#ifndef LASERTAG_WIDGETINFOBOX_H
#define LASERTAG_WIDGETINFOBOX_H

#include "HudWidget.h"
#include <string>

namespace Widgets {

    class WidgetInfoBox : public HudWidget {
    public:
        // Constructor for the class (just call base class constructor and set specific protected details)
        explicit WidgetInfoBox(int yCoordinate);


        void draw(bool force) ; // Draw the widget to the screen

        void setTexts(std::string title, std::string message); // update the text of the widget

    private:
        std::string title = "None";
        std::string message = "None";

        // last states so we know if we need to redraw
        std::string lastTitle = "None";
        std::string lastMessage = "None";
    };

} // Widgets

#endif //LASERTAG_WIDGETINFOBOX_H
