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

using namespace Gamemodes;

class GamemodeManager {

public:
    enum GamemodeOptions {
        NONE,
        SOLO
    };

    void init(LaserTag *system); // Initialise the gamemode manager

    Gamemode *getCurrentGame();

    void switchGamemode(GamemodeOptions _option);

    void switchGamemodeByInt(int _option);

    int getCurrentGamemodeOption() { return (int)currentGamemodeOption; } // Get the current gamemode option


private:
    LaserTag *mySystem; // Pointer to the main system object

    Gamemode *currentGamemode; // Pointer to the current gamemode object
    GamemodeOptions currentGamemodeOption = GamemodeOptions::NONE; // The current gamemode option
};


#endif //LASERTAG_GAMEMODES_H
