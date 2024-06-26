/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class will be used to control the TFT side display.
 * This will be used to display the game stats, menus etc.
*/

#include "SideDisplay.h"
#include "Menus/MenuManager.h"
#include <functional>

void SideDisplay::init() {
  // Set up the side display

  myRotaryEncoder.setEncoderType(EncoderType::HAS_PULLUP);
  myRotaryEncoder.setBoundaries(-1, 1, false);
  myRotaryEncoder.onTurned(std::bind(&SideDisplay::knobCallback, this, std::placeholders::_1));
  myRotaryEncoder.begin();


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

void SideDisplay::knobCallback(long value) {
  // This is the callback function for the rotary encoder

  /*
   * This works as follows:
   * The encoder starts at 0 and can go to -1, or 1 from there
   * Each time it goes to -1 or 1 we set the rotaryChange flag to that value and reset it to 0
   * Therefore we only know whether it's gone up or down.
   */

  rotaryChange = value;
  myRotaryEncoder.setEncoderValue(0);
}

void SideDisplay::pollEncoder() {
  // This gets called often to check if there's been any rotary encoder input

//  bool currentStateA = digitalRead(ROT_OUT_A);
//  if (currentStateA != lastStateA && currentStateA == 1 && !lastPress) {
//
//    // If the outputB state is different from the outputA state then
//    // the encoder is rotating CCW so decrement
//    if (digitalRead(ROT_OUT_B) != currentStateA) {
//      menuManager.onRotaryTurned(1);
//
//    } else {
//      // Encoder is rotating CW so increment
//      menuManager.onRotaryTurned(-1);
//    }
//
//    menuManager.display(false);
//  }

  if (rotaryChange != 0) { // If the flag is non-zero then we've had a rotary change
    menuManager.onRotaryTurned(rotaryChange);
    menuManager.display(false);
    rotaryChange = 0;
  }

  // check for button presses
  if (digitalRead(ROT_SWITCH) == HIGH && !lastPress) {  //button press
    lastPress = true;
    if (millis() - lastPressTime > 200) // to debounce the button wait 200ms before can be done again
      menuManager.onRotaryPressed();
    menuManager.display(false);
  }

  if (digitalRead(ROT_SWITCH) == LOW && lastPress) {  // unpress
    lastPress = false;
    lastPressTime = millis();
  }

//  lastStateA = currentStateA;

  // Put in a slight delay to help debounce the reading
//  delay(1);
}

void SideDisplay::displayMenu() {
  // Display the current menu
  menuManager.display(false);

}

Adafruit_ST7735 *SideDisplay::getRawDisplay() {
  return &sideDisplay;
}
