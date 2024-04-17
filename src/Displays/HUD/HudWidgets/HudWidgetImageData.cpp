/*
 * Created by Ed on 13/04/2024.
 *
 * This class represents a HUD widget that displays some text next to an image.
 * This will be used to display the player's health, ammo etc.
*/

#include "HudWidgetImageData.h"

using namespace HudWidgets;

HudWidgetImageData::HudWidgetImageData(Images::ImageData image, int yCoordinate) : HudWidget(yCoordinate) {

  // This is a constructor for the class that sets the image and text to display
  // We use initializer list to set the display and yCoordinate to the base class

  this->image = image;
  this->widgetHeight = 20; // Set the height of the widget to 20 pixels
}

void HudWidgetImageData::draw(bool force) {
  // Draw the widget to the screen

  if (lastData == dataFetcher() && !force) {
    return; // If the data hasn't changed then don't redraw
  }

  if (!displayAssigned) {
    return;
  }

  lastData = dataFetcher(); // Update the last data to the new data

  Adafruit_SSD1306 *actualDisplay = display->getDisplay(); // get the actual display object

  erase(); //blank out old bit

  std::string dataString = std::to_string(lastData); // Get the data to display

  actualDisplay->setTextSize(2);               // Normal 1:1 pixel scale
  actualDisplay->setTextColor(SSD1306_WHITE);  // Draw white text
  actualDisplay->setCursor(17, (yCoordinate + 2));             // Start at top-left corner
  actualDisplay->cp437(true);                  // Use full 256 char 'Code Page 437' font
  actualDisplay->write(dataString.c_str());
  display->drawImage(0, yCoordinate, image, Images::TOP_LEFT);
}

