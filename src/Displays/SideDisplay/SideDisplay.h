/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class will be used to control the TFT side display.
 * This will be used to display the game stats, menus etc.
*/

#ifndef LASERTAG_SIDEDISPLAY_H
#define LASERTAG_SIDEDISPLAY_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"  // Hardware-specific library for ST7735
#include "../ImageData.h"
#include "../../config.h"

// Pin definitions for the side display

class SideDisplay {
public:
    void init(); // Initialize the side display
    void pollEncoder(); // Poll the rotary encoder for input

private:
    Adafruit_ST7735 side_Display = Adafruit_ST7735(TFT_CS, TFT_DC,
                                                   TFT_RST); // The side display object (ST7735)
    void drawImage(int x, int y, Images::ImageData image,
                   uint16_t color, Images::OFFSET orientation);

    // variables relating to the rotary encoder
    bool lastStateA = false;
    bool lastPress = false;
    int counter = 0;
    int maxCounter = 10; // starts from 0 ends at this inclusive
    long lastPressTime = 0;
};


#endif //LASERTAG_SIDEDISPLAY_H
