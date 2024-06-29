/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This class manages all the menus in the system.
*/

#ifndef LASERTAG_MENUMANAGER_H
#define LASERTAG_MENUMANAGER_H

#include "../../ImageData.h"
#include "SelectPageMenu.h"
#include "GunMenu.h"
#include "MessageMenu.h"
#include "TypingMenu.h"
#include "CommandScrollMenu.h"

class SideDisplay;

using namespace Menus;

class MenuManager {
public:
    explicit MenuManager(SideDisplay *_sideDisplay); // constructor for the MenuManager class
    void init(); // create the menu objects

    Menu *getCurrentMenu(); // get the current menu

    void onRotaryTurned(int change); // called when the rotary encoder is turned
    void onRotaryPressed(); // called when the button is pressed

    void display(bool force); // display the menu

    void switchMenu(Menu *newMenu); // switch to a new menu
private:
    SideDisplay *sideDisplay; // pointer to the side display

    Menu *currentMenu = nullptr; // pointer to the current menu

    // Put the menus here
    SelectPageMenu mainMenu = SelectPageMenu(this, "Main Menu");
    SelectPageMenu settingsMenu = SelectPageMenu(this, "Settings");
    GunMenu gunMenu = GunMenu(this);
    MessageMenu messageMenu = MessageMenu(this);
    MessageMenu debugMsgMenu = MessageMenu(this);

    TypingMenu nameMenu = TypingMenu(this, "Name", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    TypingMenu adminPasswordMenu = TypingMenu(this, "Admin Code", "0123456789", true);
    SelectPageMenu adminMenu = SelectPageMenu(this, "Admin Menu");

    SelectPageMenu commandMenu = SelectPageMenu(this, "Commands");

    SelectPageMenu commandGamemodeMenu = SelectPageMenu(this, "Gamemodes");
//    SelectPageMenu commandPlayerMenu = SelectPageMenu(this, "Player Modifiers");
//    SelectPageMenu commandTeamMenu = SelectPageMenu(this, "Teams");
    SelectPageMenu commandWeaponsMenu = SelectPageMenu(this, "Weapons");

    CommandScrollMenu gamesCommandMenu = CommandScrollMenu(this); // holds actual games
    CommandScrollMenu gameModsCommandMenu = CommandScrollMenu(this); // holds game modifications (play/pause/etc)


};


#endif //LASERTAG_MENUMANAGER_H
