/*
 Created by Ed Fillingham on 08/04/2024.

 This is the main HUD class that will be used to control the OLED HUD (heads up display)
*/

#include "HudDisplay.h"


// definitions of various OLED screen parameters
#define SCREEN_WIDTH 128 // OLED testDisplay width, in pixels
#define SCREEN_HEIGHT 64 // OLED testDisplay height, in pixels
#define OLED_RESET     (-1) // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

void HudDisplay::init() {
  // Initialize the HUD

  // create the display object
  hudDisplay = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  // Try to set it up, else loop forever as without it the gun is useless.f
  if (!hudDisplay.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  hudDisplay.setRotation(1); // rotate it so screen is portrait


  // Clear the display for start
  hudDisplay.clearDisplay();
  hudDisplay.display();
}

void HudDisplay::setBackdrop(Images::ImageData image) {
  // Set the backdrop of the HUD to an image

  hudDisplay.clearDisplay();

  // height and width (assuming portrait orientation) must be set to 128 and 64 respectively
  // as it's a whole screen image.
  hudDisplay.drawBitmap(0, 0, image.MyImage,
                        64, 128, 1);
  hudDisplay.display();
}

void HudDisplay::drawImage(int x, int y, Images::ImageData image, Images::OFFSET orientation) {
  // Draw an image to the HUD

  // If it's centered around the x and y point then modify them
  if (orientation == Images::CENTERED) {
    x = x - (image.width / 2);
    y = y - (image.height / 2);
  }
  hudDisplay.drawBitmap((short) x, (short) y, image.MyImage,
                        (short) image.width, (short) image.height, 1);
  hudDisplay.display();
}

void HudDisplay::setState(HUD_STATE::HUD_STATE newState) {
  // Set the state of the HUD
  state = newState;
}

Adafruit_SSD1306 *HudDisplay::getDisplay() {
  return &hudDisplay;
}

void HudDisplay::loop() {
  // This function is called each time the main loop is called

  // try not to do any drawing in here as it's called a lot

  // deal with the top HUD scrolling info
  if (millis() - lastHudInfoUpdate > HUD_INFO_UPDATE_INTERVAL) {
    hudInfoState = (hudInfoState + 1) % (hudInfoStateCount);
    lastHudInfoUpdate = millis();
  }

}

void HudDisplay::setInfoStateCounts(int count) {
  // Set the number of states the HUD info can be in
  hudInfoStateCount = count;
  hudInfoState = 0;
}

int HudDisplay::getInfoStateCurrent() {
  // Return the current state of the HUD info
  return hudInfoState;
}


