#include "OledTest.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"


void oled_tester(){

#define SCREEN_WIDTH 128 // OLED testDisplay width, in pixels
#define SCREEN_HEIGHT 64 // OLED testDisplay height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
    Adafruit_SSD1306 testDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    // SSD1306_SWITCHCAPVCC = generate testDisplay voltage from 3.3V internally
    if(!testDisplay.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }


    // Clear the buffer
    testDisplay.clearDisplay();

    testDisplay.clearDisplay();
    testDisplay.setTextSize(1);
    testDisplay.setTextColor(WHITE);
    testDisplay.setCursor(0, 0);
    testDisplay.print("Display A");
    testDisplay.display();
}

