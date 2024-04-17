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
#include "../Weapons/Weapons.h"
#include "../config.h"

#define START_LIVES 3 // The maximum number of revives a player can have
#define RESPAWN_TIME 8000 // The time it takes for a player to respawn in milliseconds

class LaserTag;

class PlayerWrapper {
public:
    void init(LaserTag* _mySystem,int _unitnum, int _team); // Default constructor
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

    void setGun(std::string gunName); // Sets the player's gun
    Weapons::Gun *getGun(); // Returns the player's gun

    bool canFire(); // Returns whether the player can fire their gun
    bool canTakeDamage(int shooterUnitnum); // Returns whether the player can take damage from a shooter

    void takeDamage(int _gunIndex); // Deals damage to the player

    void respawn(); // Respawns the player
    float getRespawnStatus(); // returns 0 if not respawning, or a value 0-1 representing progress of the respawn

private:
    LaserTag* mySystem; // Pointer to the main system object

    // Details about the player
    GunTypes myGuns;
    Player player; // The player's data

    // Details about the player in this game per se
    Weapons::Gun *gun = myGuns.getGun(DEFAULT_GUN); // The player's gun (default is the Assault Rifle)
    bool respawning = false; // Whether the player is currently respawning
    unsigned long respawnStartTime = 0; // The time the player started respawning
};


#endif //LASERTAG_PLAYERWRAPPER_H
