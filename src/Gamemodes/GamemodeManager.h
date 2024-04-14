/*
 * Created by Ed Fillingham on 14/04/2024.
 *
 * This class abstracts the complexity of managing / switching gamemodes.
*/

#ifndef LASERTAG_GAMEMODES_H
#define LASERTAG_GAMEMODES_H

// Import the gamemodes here.

#include "Implementations/GamemodeNone.h"
#include "Implementations/GamemodeSolo.h"

class GamemodeManager {

public:
    enum GamemodeOptions{
        NONE,
        SOLO
    };

    explicit GamemodeManager(LaserTag *system);

    void init(); // Initialise the gamemode manager

    Gamemode *getCurrentGame();
    void switchGamemode(GamemodeOptions _option);


private:
    LaserTag *mySystem; // Pointer to the main system object

    Gamemode *currentGamemode; // Pointer to the current gamemode object
};


#endif //LASERTAG_GAMEMODES_H
