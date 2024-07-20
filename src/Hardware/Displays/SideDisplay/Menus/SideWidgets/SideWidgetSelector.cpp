/*
 * Created by Ed Fillingham on 19/04/2024.
*/

#include "SideWidgetSelector.h"

namespace SideWidgets {
    SideWidgetSelector::SideWidgetSelector(int yStart, int xStart) : SideWidget(yStart, xStart) {

    }

    void SideWidgetSelector::setHighlighted(bool highlighted) {
      // Set the highlighted state of the widget

      this->highlighted = highlighted;

    }

} // SideWidget