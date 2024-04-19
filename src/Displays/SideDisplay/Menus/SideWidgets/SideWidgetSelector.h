/*
 * Created by Ed Fillingham on 19/04/2024.
*/

#ifndef LASERTAG_SIDEWIDGETSELECTOR_H
#define LASERTAG_SIDEWIDGETSELECTOR_H

#include "SideWidget.h"

namespace SideWidgets {

    class SideWidgetSelector : public SideWidget {
    public:
        SideWidgetSelector(int yStart, int xStart); // Constructor for the class

        void setHighlighted(bool highlighted); // Set the highlighted state of the widget

        // Have lots of virtual funcs here so that we can reference SideWidgetMenuSelect etc. as SideWidgetSelector*
        virtual void setMenu() {}

        virtual Menus::Menu *getMenu() { return nullptr; }

        virtual bool hasMenuPointer() { return false; }

        virtual void setFunction() {}

        virtual std::function<void(void)> *getFunction() { return nullptr; }

        virtual bool hasFunctionPointer() { return false; }

    protected:
        // Highlighted state of the widget
        bool highlighted = false; // Whether the widget is currently highlighted
        bool lastHighlighted = false; // Whether the widget was highlighted last time it was drawn

    };

} // SideWidget

#endif //LASERTAG_SIDEWIDGETSELECTOR_H
