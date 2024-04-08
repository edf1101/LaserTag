/*
 Created by Ed Fillingham on 08/04/2024.

 This script is a class that will be used to control the OLED HUD (heads up display)
 screen on the front of the laser tag gun.
*/

#ifndef LASERTAG_HUD_H
#define LASERTAG_HUD_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class HudDisplay {
public:
    void init(); // Initialize the HUD
    void setState(); // Set the state of the HUD via enum either (SPLASH, GAME, IMAGE)
    void updatePlayerState(); // Update the player state on the HUD
private:

    Adafruit_SSD1306 ssd1306Display; // OLED testDisplay object
    void setImage(); // Set the image on the HUD
    void updateSplash(); // Update the splash screen (rotate through the animation frames)
};

#endif //LASERTAG_HUD_H
