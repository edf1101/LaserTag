/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class controls and holds all logic & variables for the entire gun / game.
 * The main.cpp or .ino file just calls this class' void init() instead of void setup()
 * and this class' void loop().
*/

#ifndef LASERTAG_LASERTAG_H
#define LASERTAG_LASERTAG_H

#include <functional>
#include "Arduino.h"
#include "Displays/HUD/HudDisplay.h"
#include "Displays/SideDisplay/SideDisplay.h"
#include "Infrared/Firing.h"
#include "Player/Player.h"
#include "Weapons/Weapons.h"
#include "Buttons/Buttons.h"
#include "Sound/SoundPlayer.h"
#include "Gamemodes/GamemodeManager.h"


class LaserTag {
public:
    void init();

    void loop();

    Player *getPlayer();

    Buttons *getButtons();

    Sounds::SoundPlayer *getSoundPlayer();

    Gamemode* getGamemode();

    HudDisplay *getHudDisplay();

    void updateHUD();

private:
    // Objects for main hardware components of the gun
    Buttons buttons;  // object representing all buttons on the gun
    HudDisplay hudDisplay;  // display objects
    SideDisplay sideDisplay;
    Sounds::SoundPlayer soundPlayer;  // sound player object

    // Objects for main software system components
    Firing firing = Firing(this);  // firing object
    Player player;  // player object
    GamemodeManager gamemodeManager = GamemodeManager(this);  // current gamemode object
};


#endif //LASERTAG_LASERTAG_H
