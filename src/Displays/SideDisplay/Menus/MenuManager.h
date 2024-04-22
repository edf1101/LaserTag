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

class SideDisplay;

using namespace Menus;

class MenuManager {
public:
    explicit MenuManager(SideDisplay* _sideDisplay); // constructor for the MenuManager class
    void init(); // create the menu objects

    Menu* getCurrentMenu(); // get the current menu

    void onRotaryTurned(int change); // called when the rotary encoder is turned
    void onRotaryPressed(); // called when the button is pressed

    void display(bool force); // display the menu

    void switchMenu(Menu *newMenu); // switch to a new menu
private:
    SideDisplay* sideDisplay; // pointer to the side display

    Menu* currentMenu = nullptr; // pointer to the current menu

    // Put the menus here
    SelectPageMenu mainMenu = SelectPageMenu(this,"Main Menu");
    SelectPageMenu settingsMenu = SelectPageMenu(this,"Settings");
    GunMenu gunMenu = GunMenu(this);
    MessageMenu messageMenu = MessageMenu(this);


};


#endif //LASERTAG_MENUMANAGER_H
