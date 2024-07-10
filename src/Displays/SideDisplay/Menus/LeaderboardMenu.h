/*
 * This is a leaderboard that gets displayed on the side display. It shows stats etc about different players.
 * Created by Ed Fillingham on 08/07/2024.
*/

#ifndef LASERTAG_LEADERBOARDMENU_H
#define LASERTAG_LEADERBOARDMENU_H

#include "Menu.h"
#include <vector>
#include <string>
#include "Arduino.h"
#include "SideWidgets/SideWidgetText.h"
#include "Players/Player.h"
#include "SideWidgets/SideWidgetPlayerInfo.h"

class MenuManager; // forward declaration

namespace Menus {

    class LeaderboardMenu : public Menu {
    public:
        explicit LeaderboardMenu(MenuManager *menuManager); // constructor for the MessageMenu class

        void init(SideDisplay *_sideDisplay, Menu *parentMenu); // This initialises the menu

        void display(bool force); // display the new menu

        void onRotaryTurned(int change); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

        void resetMenu();


    private:
        SideWidgets::SideWidgetText titleWidget = SideWidgets::SideWidgetText(2, 2, "Leaderboard", 2,
                                                                              TFT_PRIMARY_COLOUR); // the title widget

        SideWidgets::SideWidgetText returnTextWidget = SideWidgets::SideWidgetText(27, 2, "", 1,
                                                                                TFT_PRIMARY_COLOUR); // the message widget


        std::vector<SideWidgets::SideWidgetPlayerInfo> playerInfoWidgets; // vector of player info widgets

        MenuManager *menuManager; // pointer to the menu manager
        Menu *parentMenu; // pointer to the parent menu

        void updatePlayersList(); // update the players list
        std::vector<Player*> players; // vector of players

        bool lastReturnButtonShowing = false; // whether the return button was showing last time
    };

} // Menus

#endif //LASERTAG_LEADERBOARDMENU_H
