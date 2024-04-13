/*
 * Created by Ed on 13/04/2024.
 *
 * This class represents a basic HUD widget.
 * A HUD widget is a small part of the HUD that displays a specific piece of information.
 * It has smart behaviours to update itself when the information changes.
*/

#include "HudWidget.h"

using namespace Widgets;

HudWidget::HudWidget(int yStart) {
  // Constructor for the class (as base class just set the display)
  this->yCoordinate = yStart;
}

void HudWidget::init(HudDisplay *_disp) {
  // all the base class widget does in init is set the display object for the widget
  display = _disp;
  displayAssigned = true; // flag so we don't access it unassigned
}


void HudWidget::erase() {
  // Erase the widget from the screen

  if (!displayAssigned) {
    return;
  }


  display->getDisplay()->fillRect(0, yCoordinate, 64,
                                  widgetHeight, SSD1306_BLACK);
}

void HudWidget::setLocation(int y) {
  // erase old location first
  erase();
  // Set the location of the widget on the screen
  yCoordinate = y;

}


