/*
 * Created by Ed Fillingham on 16/04/2024.
 *
 * This class is a widget that when you press it, it runs a function
*/

#include "SideWidgetFunctionSelect.h"

#include <utility>
#include "../../SideDisplay.h"

namespace SideWidgets {
    SideWidgetFunctionSelect::SideWidgetFunctionSelect(int yStart, int xStart,
                                                       std::string name, Images::ImageData image, bool small)
            : SideWidgetSelector(yStart, xStart) {
      // Constructor fo the SideWidgetMenuSelect class
      this->small = small;
      if (small) { // set size
        width = 32;
        height = 32;
      } else {
        width = 40;
        height = 40;
      }

      this->name = std::move(name);
      this->icon = image;

    }

    void SideWidgetFunctionSelect::draw(bool force) {
      // Draw the widget to the screen

      if (!displayAssigned) return; // If the display hasn't been assigned, don't draw the widget

      if (lastHighlighted == highlighted && !force) return; // If the widget hasn't changed, don't redraw it
      lastHighlighted = highlighted; // Update the last highlighted state
      int colour = highlighted ? TFT_PRIMARY_COLOUR
                               : TFT_SECONDARY_COLOUR; // Set the colour of the widget based on the highlighted state

      Adafruit_ST7735 *rawDisplay = myDisplay->getRawDisplay();

      // draw a surrounding rectangle
      rawDisplay->drawRect(xStart, yStart, width, small? height: 35, colour);
      myDisplay->drawImage(xStart + 2, yStart + 2, icon, colour, // img must be 36px wide 31px tall
                           Images::OFFSET::TOP_LEFT); // Draw the icon for the widget

      if (!small) { // if its not a small widget draw title text
        rawDisplay->setTextSize(1);
        rawDisplay->setTextWrap(false);
        rawDisplay->setTextColor(colour);
        rawDisplay->setCursor(xStart, yStart + 40);
        rawDisplay->print(name.c_str()); // Draw the name of the widget
      }
    }

    void SideWidgetFunctionSelect::setFunction(std::function<void(void)> function) {
      // set the function that this widget is associated with
      this->function = function;
      hasFunction = true;
    }

    std::function<void(void)> *SideWidgetFunctionSelect::getFunction() {
      // Get the function that this widget is associated with
      return &function;
    }

    bool SideWidgetFunctionSelect::hasFunctionPointer() {
      return hasFunction;
    }


} // SideWidgets