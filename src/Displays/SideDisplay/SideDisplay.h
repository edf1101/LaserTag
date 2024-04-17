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
#include "Menus/MenuManager.h"


class SideDisplay {
public:
    SideDisplay() : menuManager(MenuManager(this)) {
    }
    void init(); // Initialize the side display
    void pollEncoder(); // Poll the rotary encoder for input

    void displayMenu();

    void drawImage(int x, int y, Images::ImageData image,
                   uint16_t color, Images::OFFSET orientation);

    Adafruit_ST7735* getRawDisplay(); // Get the display object

private:
    Adafruit_ST7735 sideDisplay = Adafruit_ST7735(TFT_CS, TFT_DC,
                                                  TFT_RST); // The side display object (ST7735)

    MenuManager menuManager; // The menu manager object

    // variables relating to the rotary encoder
    bool lastStateA = false;
    bool lastPress = false;
    unsigned long lastPressTime = 0;
};


#endif //LASERTAG_SIDEDISPLAY_H
