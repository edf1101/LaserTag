/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class will be used to control the TFT side display.
 * This will be used to display the game stats, menus etc.
*/

#include "SideDisplay.h"

void SideDisplay::init() {
  // Set up the side display

  side_Display.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  side_Display.setRotation(3); // set its rotation to be horizontal

  side_Display.fillScreen(ST7735_BLACK); // fill the screen with black
  drawImage(50, 50, Images::img_bullet, ST7735_RED, Images::CENTERED); // draw the heart image
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
  side_Display.drawBitmap((short) x, (short) y, image.MyImage,
                          (short) image.width, (short) image.height, color);
}

void SideDisplay::pollEncoder() {
  // This gets called often to check if there's been any rotary encoder input

  bool currentStateA = digitalRead(ROT_OUT_A);
  if (currentStateA != lastStateA && currentStateA == 1 && !lastPress) {

    // If the outputB state is different from the outputA state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_OUT_B) != currentStateA) {
      counter++;
    } else {
      // Encoder is rotating CW so increment
      counter--;
    }

    // These bits make sure it stays within the bounds of the counter
    if (counter < 0) {
      counter = maxCounter;
    }
    counter %= (maxCounter + 1);

    Serial.println(counter);
  }

  // check for button presses
  if (digitalRead(ROT_SWITCH) == HIGH && !lastPress) {  //button press
    lastPress = true;
    if (millis() - lastPressTime > 200) // to debounce the button wait 200ms before can be done again
      Serial.println("Button Pressed");
  }

  if (digitalRead(ROT_SWITCH) == LOW && lastPress) {  // unpress
    lastPress = false;
    lastPressTime = millis();
  }

  lastStateA = currentStateA;

  // Put in a slight delay to help debounce the reading
  delay(1);

}

