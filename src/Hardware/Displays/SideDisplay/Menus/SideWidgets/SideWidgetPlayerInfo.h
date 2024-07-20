/*
 * Created by Ed Fillingham on 08/07/2024.
 *
 * This widget is used to display player information on the side display. Primarily on the leaderboard
*/

#ifndef LASERTAG_SIDEWIDGETPLAYERINFO_H
#define LASERTAG_SIDEWIDGETPLAYERINFO_H

#include "SideWidget.h"
#include "Arduino.h"
#include "../../../../../Players/Player.h"

namespace SideWidgets {

    class SideWidgetPlayerInfo : public SideWidget {
    public:
        SideWidgetPlayerInfo(int yStart); // constructor for the class

        void setStatus(Player* newPlayer, int newRank); // Set the status of the player
        void setStatus(); // Set a blank status

        void setHighlight(bool highlight); // Set the highlight of the widget

        void draw(bool force); // Draw the widget to the screen

        void erase(); // Erase the widget from the screen
    private:
        Player* player; // The player to display information about
        int rank; // The rank of the player
        bool playerAssigned = false; // Whether a player has been assigned to the widget

        bool widgetHighlighted = false; // Whether the widget is highlighted
        bool lastWidgetHighlighted = false; // The last state of the widget being highlighted

        // last displayed details
        int lastRank = -1;
        std::string lastName;
        int lastRevives = -1;
        int lastHealth = -1;
        int lastKills = -1;
        std::string lastGun;
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGETPLAYERINFO_H
