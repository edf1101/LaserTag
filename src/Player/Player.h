/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the player's data and stats.
*/

#ifndef LASERTAG_PLAYER_H
#define LASERTAG_PLAYER_H

#include <string>
#include "Arduino.h"

#define MAX_LIVES 5; // The maximum number of revives a player can have

class Player {
public:
    void init(int _unitnum,int _team); // Default constructor
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

    void setAmmo(int ammo); // Sets the player's ammo
    int getAmmo() const; // Returns the player's ammo

    void setMags(int mags); // Sets the player's magazines
    int getMags() const; // Returns the player's magazines

    void setKills(int kills); // Sets the player's kills
    int getKills() const; // Returns the player's kills

    void setCarryingFlag(bool carryingFlag); // Sets whether the player is carrying the flag
    bool getCarryingFlag() const; // Returns whether the player is carrying the flag



private:
    int unitnum; // The player's unit number
    int team; // The player's team
    std::string name; // The player's name

    int revives = MAX_LIVES; // The number of revives the player has remaining
    u_int8_t health = 100; // The player's health 0-100 (u_int8_t is 0 - 256 so saves space)
    int ammo = 0; // The player's ammo in the current magazine
    int mags = 0; // The number of magazines the player has remaining
    int kills = 0; // The number of kills the player has
    bool carryingFlag = false; // Whether the player is carrying the flag


};


#endif //LASERTAG_PLAYER_H
