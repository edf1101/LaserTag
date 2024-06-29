/*
 * Created by Ed Fillingham on 12/04/2024.
 *
 * This represents a solo game.
*/

#ifndef FIRING_CPP_GAMEMODESOLO_H
#define FIRING_CPP_GAMEMODESOLO_H

#include "../Gamemode.h"
#include <string>

namespace Gamemodes {
    class GamemodeSolo : public Gamemode {
    public:
        GamemodeSolo(LaserTag *_mySystem); // Constructor for the class
        void loop(); // gets called every game loop call


        void drawHUD(); // Function to draw the HUD for the gamemode
        void setGamePauseState(bool pause); // Function to start the gamemode

        void onPlayerDeath(); // Gets called when the player dies

        Player getPlayerTemplate(); // Returns the player template for the gamemode

         JsonDocument getGameDetails(); // Returns the game details for the gamemode
         void loadGameDetails(JsonDocument gameDetails); // Loads the game details for the gamemode

    protected:
        enum hudStates {
            HUD_PAUSED,
            HUD_GAME,
            HUD_REVIVING
        };
        hudStates currentState = HUD_PAUSED;

        void changeHudState(hudStates newState); // Function to change the HUD state

        // HUD HudWidgets
        HudWidgets::HudWidgetBackdrop backdropWidget = HudWidgets::HudWidgetBackdrop(0, Images::img_deadRevive);
        HudWidgets::HudWidgetProgress progressWidget = HudWidgets::HudWidgetProgress(110);
        HudWidgets::HudWidgetInfoBox infoBoxWidget = HudWidgets::HudWidgetInfoBox(0);

        HudWidgets::HudWidgetImageData revivesWidget = HudWidgets::HudWidgetImageData(Images::img_revive, 35);
        HudWidgets::HudWidgetImageData healthWidget = HudWidgets::HudWidgetImageData(Images::img_heart, 60);
        HudWidgets::HudWidgetImageData ammoWidget = HudWidgets::HudWidgetImageData(Images::img_bullet, 85);
        HudWidgets::HudWidgetImageData magsWidget = HudWidgets::HudWidgetImageData(Images::img_mag, 110);

        unsigned long lastReviveHUDUpdate = 0;


    };
}


#endif //FIRING_CPP_GAMEMODESOLO_H
