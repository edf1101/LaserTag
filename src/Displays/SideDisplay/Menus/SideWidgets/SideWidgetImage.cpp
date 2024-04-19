/*
 * Created by Ed Fillingham on 17/04/2024.
 *
 * This widget is used to display images on the side display.
*/

#include <utility>
#include "SideWidgetImage.h"
#include "../../SideDisplay.h"

namespace SideWidgets {
    SideWidgetImage::SideWidgetImage(int yStart, int xStart, Images::ImageData image, uint16_t colour)
            : SideWidget(yStart, xStart) {
      // Constructor for the class

      this->image = std::move(image); // Set the image to the image passed in
      this->width = image.width;
      this->height = image.width;
      this->colour = colour;
    }

    void SideWidgetImage::draw(bool force) {
      // Draw the widget to the screen

      if (!displayAssigned) return; // If the display hasn't been assigned, return

      if (image.MyImage != lastImage.MyImage) {
        // If the image has changed, force a redraw
        force = true;
      }

      if (!force) { // If we don't want to force a redraw return
        return;
      }
      erase(); // Erase the old image from the screen

      myDisplay->drawImage(this->xStart, this->yStart, this->image, colour,
                           Images::OFFSET::TOP_LEFT); // Draw the image to the screen
    }

    void SideWidgetImage::setImage(Images::ImageData image) {
      // Set the image to display
      this->image = std::move(image); // Set the image to the image passed in
      this->width = image.width;
      this->height = image.height;
    }
} // SideWidgets