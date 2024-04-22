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
#include "Players/PlayerWrapper.h"
#include "Weapons/WeaponsManager.h"
#include "Buttons/Buttons.h"
#include "Sound/SoundPlayer.h"
#include "Gamemodes/GamemodeManager.h"
#include "config.h"
#include "LEDs/LEDManager.h"
#include "Network/Network.h"


class LaserTag {
public:
    void init();

    void loop();

    bool canFire();

    bool canTakeDamage(int shooterUnitnum);

    void updateHUD();

    static void turnOff();

    // Getters for Pointers to various system components (below)
    static PlayerWrapper *getPlayer();

    static Buttons *getButtons();

    static Sounds::SoundPlayer *getSoundPlayer();

    Gamemode *getGamemode();

    static HudDisplay *getHudDisplay();

    static LEDs::LEDManager *getLEDManager();

    static Networks::Network *getNetworkManager();

private:
    // Objects for main hardware components of the gun.
    inline static Buttons buttons;  // object representing all buttons on the gun.
    inline static HudDisplay hudDisplay;  // HUD display object.
    inline static SideDisplay sideDisplay; // Side display object.
    inline static Sounds::SoundPlayer soundPlayer;  // sound player object.
    inline static LEDs::LEDManager ledManager; // LED manager object.
    inline static Networks::Network networkManager; // Network object.

    // Objects for main software system components
    Firing firing = Firing(this);  // firing object
    inline static PlayerWrapper player;  // player object
    GamemodeManager gamemodeManager = GamemodeManager(this);  // current gamemode object
};


#endif //LASERTAG_LASERTAG_H
