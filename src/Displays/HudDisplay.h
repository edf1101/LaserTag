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

// includes for images
#include "ImageData.h"


namespace HUD_STATE { // container for the HUD_STATE enum

    enum HUD_STATE {
        // This enum represents states that the HUD can be in
        SPLASH, // On the animated (or not) splash screen
        IMAGE, // Showing a single (whole screen) image on the HUD
        GAME_REGULAR, // In regular game (so it shows the HUD stats)
        // may have GAME_HUNTED etc. afterwards if needed
    };
}

class HudDisplay {
public:
    void init();
    void setState(HUD_STATE::HUD_STATE newState); // Set the state of the HUD via enum either (SPLASH, GAME, IMAGE)
    void updatePlayerState(); // Update the player state on the HUD
private:
    HUD_STATE::HUD_STATE state; // The current state of the HUD
    Adafruit_SSD1306 hudDisplay; // OLED testDisplay object
    void setBackdrop(ImageData::ImageData image); // Set a whole screen image on the HUD
    void drawImage(int x, int y, ImageData::ImageData image,
                   ImageData::OFFSET orientation = ImageData::TOP_LEFT); // Draw an image on the HUD
    void updateSplash(); // Update the splash screen (rotate through the animation frames)
};

#endif //LASERTAG_HUD_H
