/*
 * Created by Ed Fillingham on 19/04/2024.
 *
 * This class is a menu that allows the user to select a gun.
*/

#ifndef LASERTAG_GUNMENU_H
#define LASERTAG_GUNMENU_H

#include "../../../Weapons/WeaponsManager.h"
#include <functional>
#include <vector>
#include "Menu.h"
#include "SideWidgets/SideWidgetSubMenu.h"
#include "SideWidgets/SideWidgetText.h"
#include "SideWidgets/SideWidgetImage.h"

class MenuManager; // forward declaration

namespace Menus {

    class GunMenu : public Menu {
    public:
        GunMenu(MenuManager* myMenuManager); // constructor for the class
        void init(SideDisplay *sideDisplay, Menu* previousMenu); // initialise the menu

        void display(bool force); // display the menu

        void onRotaryTurned(int change); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

        void resetMenu(); // reset the menu

        void fetchGunsInUse(); // fetch the guns in use

    private:
        void subMenuCounterChanged(int item); // called when a new gun is shown in sub menu
        void subMenuCounterPressed(int item); // called when a gun is selected by sub menu


        std::vector<Weapons::Gun> gunsInUse; // vector of guns in use

        MenuManager* menuManager; // Reference to the menu manager

        // The sub menu widget that will be displayed on the side display
        SideWidgets::SideWidgetSubMenu subMenu = SideWidgets::SideWidgetSubMenu(160-32, 0);

        SideWidgets::SideWidgetImage gunImage = SideWidgets::SideWidgetImage(2,2, Images::img_bullet,ST7735_RED);
        SideWidgets::SideWidgetText gunName = SideWidgets::SideWidgetText(57,2, "Name: Glock-18",1,ST7735_RED);
        SideWidgets::SideWidgetText gunAmmo = SideWidgets::SideWidgetText(67,2, "Ammo: 30",1,ST7735_RED);
        SideWidgets::SideWidgetText gunMags = SideWidgets::SideWidgetText(77,2, "Mags: 100",1,ST7735_RED);
        SideWidgets::SideWidgetText gunFireType = SideWidgets::SideWidgetText(87,2, "Type: BURST",1,ST7735_RED);
        SideWidgets::SideWidgetText gunFireRate = SideWidgets::SideWidgetText(97,2, "Speed: 2 bullets/s",1,ST7735_RED);
        SideWidgets::SideWidgetText gunDamage = SideWidgets::SideWidgetText(107,2, "Damage: 10",1,ST7735_RED);
        SideWidgets::SideWidgetText gunSuppressed = SideWidgets::SideWidgetText(117,2, "Suppressed?: FALSE",1,ST7735_RED);

    };
}

#endif //LASERTAG_GUNMENU_H
