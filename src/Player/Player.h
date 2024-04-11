/*
 *  Created by Ed Fillingham on 09/04/2024.
 *
 *  This class will be used to store the player's data and stats.
*/

#ifndef LASERTAG_PLAYER_H
#define LASERTAG_PLAYER_H

#include <string>
#include "Arduino.h"
#include "../Weapons/Weapons.h"

#define START_LIVES 3; // The maximum number of revives a player can have

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

    void setKills(int kills); // Sets the player's kills
    int getKills() const; // Returns the player's kills

    void setCarryingFlag(bool carryingFlag); // Sets whether the player is carrying the flag
    bool getCarryingFlag() const; // Returns whether the player is carrying the flag

    void setGun(Weapons::Gun* gun); // Sets the player's gun
    Weapons::Gun* getGun() ; // Returns the player's gun



private:
    GunTypes myGuns;
    int unitnum; // The player's unit number
    int team; // The player's team
    std::string name; // The player's name

    int revives = START_LIVES; // The number of revives the player has remaining
    u_int8_t health = 100; // The player's health 0-100 (u_int8_t is 0 - 256 so saves space)
    int kills = 0; // The number of kills the player has
    bool carryingFlag = false; // Whether the player is carrying the flag
    Weapons::Gun* gun = myGuns.getGun("Assault Rifle"); // The player's gun (default is the Assault Rifle)

};


#endif //LASERTAG_PLAYER_H
