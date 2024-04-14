/*
 * Created by Ed Fillingham on 12/04/2024.
 *
 * This represents a solo game.
*/

#ifndef FIRING_CPP_GAMEMODESOLO_H
#define FIRING_CPP_GAMEMODESOLO_H

#include "../Gamemode.h"
#include <string>


    class GamemodeSolo : public Gamemode {
    public:
        GamemodeSolo(LaserTag *_mySystem); // Constructor for the class

        void drawHUD(); // Function to draw the HUD for the gamemode
        void setGamePauseState(bool pause); // Function to start the gamemode

    protected:
        enum hudStates {
            HUD_PAUSED,
            HUD_GAME,
            HUD_REVIVING
        };
        hudStates currentState = HUD_PAUSED;

        void changeHudState(hudStates newState); // Function to change the HUD state

        // HUD Widgets
        Widgets::WidgetBackdrop backdropWidget = Widgets::WidgetBackdrop(0, Images::img_deadRevive);
        Widgets::WidgetProgress progressWidget = Widgets::WidgetProgress(0);
        Widgets::WidgetInfoBox infoBoxWidget = Widgets::WidgetInfoBox(0);

        Widgets::WidgetImageData revivesWidget = Widgets::WidgetImageData(Images::img_revive, 35);
        Widgets::WidgetImageData healthWidget = Widgets::WidgetImageData(Images::img_heart, 60);
        Widgets::WidgetImageData ammoWidget = Widgets::WidgetImageData(Images::img_bullet, 85);
        Widgets::WidgetImageData magsWidget = Widgets::WidgetImageData(Images::img_mag, 110);

    };



#endif //FIRING_CPP_GAMEMODESOLO_H
