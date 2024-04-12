/*
 * Created by Ed Fillingham on 12/04/2024.
 *
 * This class represents a basic gamemode in the Laser Tag system.
 * This is an abstract class (so can't be instantiated) that other gamemodes will inherit from.
*/

#ifndef FIRING_CPP_GAMEMODE_H
#define FIRING_CPP_GAMEMODE_H

#include <string>
#include "../Displays/HudDisplay.h"

class LaserTag;

class Gamemode {
public:
    Gamemode(LaserTag* _mySystem); // Constructor for the base gamemode class

    void initialisePlayer(); // Function to initialise the player for the gamemode
    void startGame(); // Function to start the gamemode

    // Getters for gamemode details
    std::string getName(); // Get the name of the gamemode

    bool canFire(); // Function to check if the player can fire according to the gamemode state
    void drawHUD(); // Function to draw the HUD for the gamemode

    // Event functions (These get called when something happens, eg. player dies)
    virtual void onPlayerDeath(); // Called when a player dies
    virtual void onPickupRespawn(); // Called when a player gets a respawn signal
    virtual void onPickupFlag(); // Called when a player picks up the flag
    virtual void onDropFlag(); // Called when a player drops the flag


protected:
    LaserTag* mySystem; // Reference to the main LaserTag system object
    HudDisplay* displayHud; // Reference to the display object

    // Details about the gamemode itself
    std::string name = "Base Gamemode";
    bool teamBased = false;
    int playerStartingRevives = 3;

    // Details about the gamemode instance (often relating to the player)
    bool started = false;
};


#endif //FIRING_CPP_GAMEMODE_H
