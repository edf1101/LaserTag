/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This struct represents a player in the game.
 * for our own gun it is handled by the PlayerWrapper class. For other guns it'll be handled elsewhere.
*/

#ifndef LASERTAG_PLAYER_H
#define LASERTAG_PLAYER_H

#include <string>

struct Player {
    // Details about the player
    int unitnum; // The player's unit number
    int team; // The player's team (-1 means solo)
    std::string name; // The player's name

    // Details about the player in this game per se
    int revives; // The number of revives the player has remaining
    int health; // The player's health 0-100 (u_int8_t is 0 - 256 so saves space)
    int kills; // The number of kills the player has
    bool carryingFlag; // Whether the player is carrying the flag
    int gunIndex; // The index of the gun the player is using

};

#endif //LASERTAG_PLAYER_H
