/*
 * Created by Ed Fillingham on 13/04/2024.
 *
 * This gamemode represents when no gamemode is selected. It is the default gamemode.
*/

#ifndef LASERTAG_GAMEMODENONE_H
#define LASERTAG_GAMEMODENONE_H

#include "../Gamemode.h"


    class GamemodeNone : public Gamemode {
    public:
        GamemodeNone(LaserTag *_mySystem); // Constructor for this gamemode
        void setGamePauseState(bool pause); // Start the game (override so it does nothing)

        void drawHUD(); // Draw the HUD (always displays no game message)
        void initialisePlayer(); // Initialise the player (override so does nothing)
        bool canFire(); // Can the player fire (override so always returns false)
    private:

        // HUD Widgets
        Widgets::WidgetInfoBox infoWidget = Widgets::WidgetInfoBox(0);
    };


#endif //LASERTAG_GAMEMODENONE_H
