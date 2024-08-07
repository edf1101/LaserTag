/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the player's data and stats.
*/

#ifndef LASERTAG_PLAYERWRAPPER_H
#define LASERTAG_PLAYERWRAPPER_H

#include <string>
#include <functional>
#include "Arduino.h"
#include "Player.h"
#include "../Weapons/WeaponsManager.h"
#include "../config.h"


#define RESPAWN_TIME 8000 // The time it takes for a player to respawn in milliseconds
#define MAX_REVIVES 10 // Can have up to (MAX_LIVES) revives inclusive

class LaserTag;

class PlayerWrapper {

public:
    // This enum describes the state of the player's infinite lives
    enum InfiniteLivesState {
        NORMAL_LIVES,
        INVINCIBLE_LIVES, // cannot take damage
        INFINITE_LIVES, // can take damage but won't use revives to respawn
    };

    void init(int _team); // Default constructor
    void loop(); // Function to be called every loop

    int getUnitnum() const; // Returns the player's unit number
    void setUnitnum(int _unitnum); // Sets the player's unit number

    int getTeam() const; // Returns the player's team
    void setTeam(int _team); // Sets the player's team

    std::string getName() const; // Returns the player's name
    void setName(std::string _name); // Sets the player's name

    int getRevives() const; // Returns the number of revives the player has remaining
    void setRevives(int _revives); // Sets the number of revives the player has remaining

    void setHealth(int health); // Sets the player's health
    int getHealth() const; // Returns the player's health

    void setKills(int kills); // Sets the player's kills
    int getKills() const; // Returns the player's kills

    void setCarryingFlag(bool carryingFlag); // Sets whether the player is carrying the flag
    bool getCarryingFlag() const; // Returns whether the player is carrying the flag

    Weapons::Gun *getGun(); // Returns the player's gun
    void swapGun(std::string gunName); // Swaps the player's gun
    void resetGun(); // Resets the player's gun

    bool canFire(); // Returns whether the player can fire their gun
    bool canTakeDamage(int shooterUnitnum); // Returns whether the player can take damage from a shooter

    void takeDamage(int _gunIndex); // Deals damage to the player

    void respawn(); // Respawns the player
    float getRespawnStatus(); // returns 0 if not respawning, or a value 0-1 representing progress of the respawn

    static void setPlayerToTemplate(Player *target, Player templatePlayer); // Sets the target player to a template
    void setPlayerToTemplate(Player templatePlayer); // Sets the player to the template player

    void setInfiniteLivesState(InfiniteLivesState state); // Sets the player's infinite lives state
    InfiniteLivesState getInfiniteLivesState(); // Returns the player's infinite lives state

private:
    LaserTag *mySystem; // Pointer to the main system object

    // Details about the player
    Player player; // The player's data
    bool customName = false; // Whether the player has a custom name

    // Details about the player in this game per se
    Weapons::Gun gun = WeaponsManager::getGun("Assault Rifle"); // The player's gun (default is the Assault Rifle)
    bool respawning = false; // Whether the player is currently respawning
    unsigned long respawnStartTime = 0; // The time the player started respawning

    InfiniteLivesState currentInfiniteLivesState = NORMAL_LIVES; // The player's current infinite lives state
};


#endif //LASERTAG_PLAYERWRAPPER_H
