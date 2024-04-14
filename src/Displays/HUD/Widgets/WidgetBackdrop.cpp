/*
 * Created by Ed Fillingham on 13/04/2024.
*/

#include "WidgetBackdrop.h"

using namespace Widgets;

WidgetBackdrop::WidgetBackdrop(int yStart, Images::ImageData background)
        : HudWidget(yStart) {
  // Constructor for the class (as base class just set the display)
  this->background = background;
  widgetHeight =128;
}

void WidgetBackdrop::setBackground(Images::ImageData background) {
  // Set the background image of the widget
  this->background = background;
}

void WidgetBackdrop::draw(bool force) {
  // Draw the widget to the screen
  if (!displayAssigned) {
    return;
  }

  display->setBackdrop(background);
}