/*
 * Created by Ed Fillingham on 19/04/2024.
*/

#ifndef LASERTAG_SIDEWIDGETSUBMENU_H
#define LASERTAG_SIDEWIDGETSUBMENU_H

#include <functional>
#include "SideWidgetFunctionSelect.h"
#include "SideWidget.h"
#include "../../../ImageData.h"

class MenuManager;

namespace SideWidgets {

    class SideWidgetSubMenu : public SideWidget {
    public:
        SideWidgetSubMenu(int xStart, int yStart); // constructor for the class
        void init(SideDisplay *sideDisplay, MenuManager* menuManager, Menus::Menu* prevMenu); // Initialise the widget (set the display object

        void draw(bool force); // Draw the widget to the screen

        void onRotaryTurned(int newValue); // called when the rotary encoder is turned
        void onRotaryPressed(); // called when the button is pressed

        void reset(); // Reset the submenu

        void setMaxSubMenuCounter(int maxSubMenuCounter); // Set the maximum number of buttons in the sub menu

        void setCounterChangedCallback(std::function<void(int)> callback); // Set the callback for when the sub menu counter changes
        void setCounterPressedCallback(std::function<void(int)> callback); // Set the callback for when the sub menu counter is pressed
    private:
        std::function<void(int)> onChangeSubMenuCounter;
        bool changeCallbackSet = false;

        std::function<void(int)> onPressSubMenuCounter;
        bool pressCallbackSet = false;

        MenuManager *menuManager; // Reference to the menu manager
        Menus::Menu *previousMenu; // Reference to the previous menu

        int rotaryCounter = 0; // The currently selected button

        int subMenuCounter = 0; // The currently selected button in the sub menu
        int maxSubMenuCounter = 3; // The maximum number of buttons in the sub menu


        // References to the buttons in the sub menu
        SideWidgetFunctionSelect upButton = SideWidgetFunctionSelect(0, 128, "Up", Images::img_rightArrow, true);
        SideWidgetFunctionSelect downButton = SideWidgetFunctionSelect(32, 128, "Down", Images::img_leftArrow, true);
        SideWidgetFunctionSelect selectButton = SideWidgetFunctionSelect(64, 128, "Select", Images::img_subMenuSelect, true);
        SideWidgetFunctionSelect returnButton = SideWidgetFunctionSelect(96, 128, "Return", Images::img_subMenuReturn, true);

        void increaseSubMenuCounter();

        void decreaseSubMenuCounter();

        void selectOption();

        void returnToParent();
    };

} // SideWidgets

#endif //LASERTAG_SIDEWIDGETSUBMENU_H
