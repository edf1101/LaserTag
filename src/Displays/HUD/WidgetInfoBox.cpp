/*
 * Created by Ed on 13/04/2024.
 *
 * This class represents a HUD widget that displays Two lines of text (title and message).
 * This will be used to notify of kills,teams etc.
*/

#include "WidgetInfoBox.h"

#include <utility>

using namespace Widgets;

WidgetInfoBox::WidgetInfoBox(int yCoordinate) : HudWidget(yCoordinate) {
  widgetHeight = 30;
}

void WidgetInfoBox::setTexts(std::string _title, std::string _message) {
  // Set the text to display
  this->title = std::move(_title);
  this->message = std::move(_message);
}

void WidgetInfoBox::draw() {
  // Draw the widget to the screen

  if (!displayAssigned) { // check display is set
    return;
  }

  // check if the text has changed
  if (title == lastTitle && message == lastMessage) {
    return;
  }

  erase(); // erase the old stuff

  // start drawing the new stuff
  Adafruit_SSD1306* actualDisplay = display->getDisplay(); // get the actual display object

  actualDisplay->setTextSize(2);               // Normal 1:1 pixel scale
  actualDisplay->setTextColor(SSD1306_WHITE);  // Draw white text
  actualDisplay->setTextWrap(false);
  actualDisplay->setCursor(0, (short) (yCoordinate));             // Start at top-left corner
  actualDisplay->cp437(true);                  // Use full 256 char 'Code Page 437' font

  actualDisplay->write(title.c_str());

  actualDisplay->setTextSize(1);               // Normal 1:1 pixel scale
  actualDisplay->setCursor(0, (short) (yCoordinate + 18));             // Start at top-left corner

  actualDisplay->write(message.c_str());
}
