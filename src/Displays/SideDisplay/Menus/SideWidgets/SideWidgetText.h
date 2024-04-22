/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This widget is used to display text eg titles, subtitles, etc on the side display.
*/

#ifndef LASERTAG_SIDEWIDGETTEXT_H
#define LASERTAG_SIDEWIDGETTEXT_H

#include <string>
#include "Arduino.h"
#include "SideWidget.h"

namespace SideWidgets {

    class SideWidgetText : public SideWidget{
    public:
        SideWidgetText(int yStart, int xStart, std::string text, int textSize, uint16_t textColor = ST7735_WHITE); // Constructor for the class
        void setText(std::string newText); // Set the text to display
        void draw(bool force); // Draw the widget to the screen
    private:
        uint16_t textColor; // The colour of the text
        std::string text; // The text to display
        int textSize; // The size of the text

        uint16_t lastTextColor = ST7735_BLACK; // The last colour of the text
        std::string lastText = ""; // The last text to display
        int lastTextSize = 0; // The last size of the text
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGETTEXT_H
