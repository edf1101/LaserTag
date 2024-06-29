/*
 * Created by Ed Fillingham on 13/04/2024.
 *
 * This gamemode represents when no gamemode is selected. It is the default gamemode.
*/

#ifndef LASERTAG_GAMEMODENONE_H
#define LASERTAG_GAMEMODENONE_H

#include "../Gamemode.h"

namespace Gamemodes {
    class GamemodeNone : public Gamemode {
    public:
        GamemodeNone(LaserTag *_mySystem); // Constructor for this gamemode
        void setGamePauseState(bool pause); // Start the game (override so it does nothing)

        void drawHUD(); // Draw the HUD (always displays no game message)
        void initialisePlayer(); // Initialise the player (override so does nothing)
        bool canFire(); // Can the player fire (override so always returns false)
        bool canTakeDamage(int shooterUnitnum); // Can the player take damage (override so always returns false)

        Player getPlayerTemplate(); // Returns the player template for the gamemode

        // Game details functions are no different to the base gamemode one as the only game specific variable is started var
    private:

        // HUD HudWidgets
        HudWidgets::HudWidgetInfoBox infoWidget = HudWidgets::HudWidgetInfoBox(0);
    };
}

#endif //LASERTAG_GAMEMODENONE_H
