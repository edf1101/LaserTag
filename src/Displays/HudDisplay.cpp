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
    ssd1306Display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    // Try to set it up, else loop forever as without it the gun is useless.f
    if(!ssd1306Display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }


    // Clear the buffer
    ssd1306Display.clearDisplay();
    setImage(ImageData::img_bullet);
    ssd1306Display.display();
}

void HudDisplay::setImage(ImageData::ImageData image){

    ssd1306Display.clearDisplay();

    ssd1306Display.drawBitmap(20, 20, image.MyImage,
                              (short)image.width,
                              (short)image.height,1);
    ssd1306Display.display();
}