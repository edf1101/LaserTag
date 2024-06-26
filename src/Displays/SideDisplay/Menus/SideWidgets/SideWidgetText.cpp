/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This widget is used to display text eg titles, subtitles, etc on the side display.
*/

#include <utility>
#include "SideWidgetText.h"
#include "../../SideDisplay.h"

namespace SideWidgets {
    SideWidgetText::SideWidgetText(int yStart, int xStart, std::string text, int textSize, uint16_t textColor)
            : SideWidget(yStart, xStart) {
      // Constructor for the class

      this->text = std::move(text);
      this->textSize = textSize;
      this->textColor = textColor;
      this->width = textSize * text.length() * 8;
      this->height = textSize * 8;
    }

    void SideWidgetText::draw(bool force) {
      // Draw the widget to the screen

      if (!displayAssigned) return; // If the display hasn't been assigned, return

      // return if text, text size, colour is different to the last time the widget was drawn or force more

      if (text == lastText && textSize == lastTextSize && textColor == lastTextColor && !force) return;


      // Overwrite old text
      Adafruit_ST7735 *rawDisplay = myDisplay->getRawDisplay();
      rawDisplay->setTextSize(lastTextSize); // Set the text size
      rawDisplay->setTextColor(ST7735_BLACK); // Set the text colour
      rawDisplay->setTextWrap(false); // Wrap the text
      rawDisplay->setCursor(xStart, yStart); // Set the cursor to the top left corner of the widget
      rawDisplay->print(lastText.c_str()); // Print the text

      lastText = text; // Set the last text to the current text
      lastTextSize = textSize; // Set the last text size to the current text size
      lastTextColor = textColor; // Set the last text colour to the current text colour

      // Actually draw the text
      rawDisplay->setTextSize(textSize); // Set the text size
      rawDisplay->setTextColor(textColor); // Set the text colour
      rawDisplay->setTextWrap(false); // Wrap the text
      rawDisplay->setCursor(xStart, yStart); // Set the cursor to the top left corner of the widget
      rawDisplay->print(text.c_str()); // Print the text

    }

    void SideWidgetText::setText(std::string newText) {
      // update the text field
      text = std::move(newText);
    }
} // SideWidgets