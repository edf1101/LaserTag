/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class will be used to control the TFT side display.
 * This will be used to display the game stats, menus etc.
*/

#include "SideDisplay.h"
#include "Menus/MenuManager.h"
#include <functional>
#include "../../Buttons/Buttons.h"
#include "../../LaserTag.h"

void SideDisplay::init() {
  // Set up the side display

  // set up rotary press button
  this->rotaryPressButton = &LaserTag::getButtons()->rotaryButton;
  rotaryPressButton->SetReleasedCallback(std::bind(&SideDisplay::rotaryPressCallback, this));


  LaserTag::getButtons()->rotaryEncoder.setCallbackFunc(std::bind(&SideDisplay::onRotaryChange,
                                                                  this, std::placeholders::_1));

  sideDisplay.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  sideDisplay.setRotation(3); // set its rotation to be horizontal

  sideDisplay.fillScreen(ST7735_BLACK); // fill the screen with black

  menuManager.init();
}

void SideDisplay::drawImage(int x, int y, Images::ImageData image,
                            uint16_t color = ST7735_WHITE,
                            Images::OFFSET orientation = Images::TOP_LEFT) {
  // Draw an image to the Side screen

  // If it's centered around the x and y point then modify them
  if (orientation == Images::CENTERED) {
    x = x - (image.width / 2);
    y = y - (image.height / 2);
  }
  sideDisplay.drawBitmap((short) x, (short) y, image.MyImage,
                         (short) image.width, (short) image.height, color);
}

void SideDisplay::rotaryPressCallback() {
  // This is the callback function for the rotary encoder button press

  if (millis() - lastPressTime > 200) {// to debounce the button wait ~200ms before can be done again
    menuManager.onRotaryPressed();
    menuManager.display(false);
    lastPressTime = millis();
  }
}

void SideDisplay::displayMenu() {
  // Display the current menu
  menuManager.display(false);

}

Adafruit_ST7735 *SideDisplay::getRawDisplay() {
  return &sideDisplay;
}

void SideDisplay::onRotaryChange(int change) {
  // This function is called when the rotary encoder is turned

  menuManager.onRotaryTurned(change);
  menuManager.display(false);
}

MenuManager *SideDisplay::getMenuManager() {
  // Get the menu manager object

    return &menuManager;
}
