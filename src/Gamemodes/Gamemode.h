/*
 * Created by Ed Fillingham on 12/04/2024.
 *
 * This class represents a basic gamemode in the Laser Tag system.
 * This is an abstract class (so can't be instantiated) that other gamemodes will inherit from.
*/

#ifndef FIRING_CPP_GAMEMODE_H
#define FIRING_CPP_GAMEMODE_H

#include <string>
#include "ArduinoJson.h"
#include "Players/Player.h"
#include "../Displays/HUD/HudDisplay.h"
#include "../Displays/HUD/HudWidgets/HudWidgetImageData.h"
#include "../Displays/HUD/HudWidgets/HudWidgetInfoBox.h"
#include "../Displays/HUD/HudWidgets/HudWidgetBackdrop.h"
#include "../Displays/HUD/HudWidgets/HudWidgetProgress.h"


#define HUD_UPDATE_INTERVAL 5000 // force an update on the HUD every 5 seconds automatically

class LaserTag;

namespace Gamemodes {

    class Gamemode {
    public:
        Gamemode(LaserTag *_mySystem); // Constructor for the base gamemode class


        virtual void setGamePauseState(bool paused); // Function to set the game pause state

        virtual void loop(); // This is called each time the main loop is called

        // Getters for gamemode details
        static std::string getName(); // Get the name of the gamemode

        virtual bool canFire(); // Function to check if the player can fire according to the gamemode state
        virtual bool canTakeDamage(
                int shooterUnitnum); // Function to check if the player can take damage according to the gamemode state

        virtual void drawHUD(); // Function to draw the HUD for the gamemode

        // Event functions (These get called when something happens, eg. player dies)
        virtual void onPlayerDeath(); // Called when a player dies
        virtual void onPickupRespawn(); // Called when a player gets a respawn signal
        virtual void onPickupFlag(); // Called when a player picks up the flag
        virtual void onDropFlag(); // Called when a player drops the flag

        virtual Player getPlayerTemplate(); // Returns the player template for the gamemode

        virtual JsonDocument getGameDetails(); // Returns the game details for the gamemode
        virtual void loadGameDetails(JsonDocument gameDetails); // Loads the game details for the gamemode

    protected:
        LaserTag *mySystem; // Reference to the main LaserTag system object
        PlayerWrapper *myPlayer; // Reference to the player object
        HudDisplay *displayHud = nullptr; // Reference to the display object

        // Details about the gamemode itself
        inline static std::string name = "Base Gamemode";
        bool teamBased = false;
        int playerStartingRevives = 3;

        // Details about the gamemode instance (often relating to the player)
        bool started = false;

        unsigned long lastHudAutoUpdate = 0; // So we update the HUD every so often
    };
}

#endif //FIRING_CPP_GAMEMODE_H
