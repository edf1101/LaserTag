

#ifndef LASERTAG_MENU_H
#define LASERTAG_MENU_H

class SideDisplay;

#include "Arduino.h"
#include "../../config.h"

namespace Menus {

    class Menu {
    public:
        Menu(); // constructor for the Menu class
        void init(SideDisplay *_sideDisplay);


        virtual void display(bool force); // display the menu

        void erase(); // erase the whole screen of menu

        void setRotaryMax(int max); // set the maximum value for the rotary encoder
        virtual void onRotaryTurned(int change); // called when the rotary encoder is turned
        virtual void onRotaryPressed(); // called when the button is pressed

        bool getCanTakeDamage(); // get whether you can take damage in this menu

        void setParentMenu(Menu* parent); // set the parent menu

        virtual void resetMenu(); // reset the menu

    protected:
      SideDisplay* sideDisplay; // pointer to the side display

      bool canTakeDamage = true; // whether you can take damage in this menu

      Menu* parentMenu = nullptr; // pointer to the parent menu
      bool hasParentMenu = false; // whether the menu has a parent menu

      int rotaryCounter = 0; // The current counter on the rotary encoder
      int maxRotaryCounter = 1; // The maximum counter on the rotary encoder

    };

} // Menus

#endif //LASERTAG_MENU_H
