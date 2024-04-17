/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This class represents a basic side widget.
*/

#include "SideWidget.h"
#include "../../SideDisplay.h"

namespace SideWidgets {
    SideWidget::SideWidget(int yStart, int xStart) {
      // Constructor for the class - assign the display and set the location and size of the widget
      this->yStart = yStart;
      this->xStart = xStart;
    }

    void SideWidget::init(SideDisplay* myDisplay) {
      // Assign the display object to the widget
      this->myDisplay = myDisplay;
      this->displayAssigned = true;
    }

    void SideWidget::erase() {
      Adafruit_ST7735 *rawDisplay = myDisplay->getRawDisplay();
      // Erase the widget from the screen
      rawDisplay->fillRect(xStart, yStart, width, height, ST7735_BLACK);
    }
} // SideWidgets