/*
 * Created by Ed Fillingham on 16/04/2024.
*/

#include "SideWidgetMenuSelect.h"
#include "../../SideDisplay.h"

namespace SideWidgets {
    SideWidgetMenuSelect::SideWidgetMenuSelect(int yStart, int xStart,
                                               std::string name, Images::ImageData image)
            : SideWidgetSelector(yStart, xStart) {
      // Constructor fo the SideWidgetMenuSelect class
      width = 40;
      height = 40;
      this->name = name;
      this->icon = image;

    }

    void SideWidgetMenuSelect::draw(bool force) {
      // Draw the widget to the screen

      if (!displayAssigned) return; // If the display hasn't been assigned, don't draw the widget

      if (lastHighlighted == highlighted && !force) return; // If the widget hasn't changed, don't redraw it
      lastHighlighted = highlighted; // Update the last highlighted state

      int colour = highlighted ? ST7735_WHITE
                               : ST7735_RED; // Set the colour of the widget based on the highlighted state

      Adafruit_ST7735 *rawDisplay = myDisplay->getRawDisplay();

      // draw a surrounding rectangle
      rawDisplay->drawRect(xStart, yStart, width, 35, colour);
      myDisplay->drawImage(xStart + 2, yStart + 2, icon, colour, // img must be 36px wide 31px tall
                           Images::OFFSET::TOP_LEFT); // Draw the icon for the widget

      rawDisplay->setTextSize(1);
      rawDisplay->setTextWrap(false);
      rawDisplay->setTextColor(colour);
      rawDisplay->setCursor(xStart, yStart + 40);
      rawDisplay->print(name.c_str()); // Draw the name of the widget


    }



    Menu *SideWidgetMenuSelect::getMenu() {
      // Get the menu that this widget is associated with

      return menu;
    }

    void SideWidgetMenuSelect::setMenu(Menus::Menu *menu) {
      // Set the menu that this widget is associated with

      this->menu = menu;
      hasMenu = true;
    }

    bool SideWidgetMenuSelect::hasMenuPointer() {
      return hasMenu;
    }
} // SideWidgets