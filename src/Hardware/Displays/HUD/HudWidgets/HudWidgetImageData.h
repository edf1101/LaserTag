/*
 * Created by Ed on 13/04/2024.
 *
 * This class represents a HUD widget that displays some text next to an image.
 * This will be used to display the player's health, ammo etc.
*/

#ifndef LASERTAG_HUDWIDGETIMAGEDATA_H
#define LASERTAG_HUDWIDGETIMAGEDATA_H

#include <string>
#include <functional>
#include <utility>
#include "HudWidget.h"
#include "../../ImageData.h"


namespace HudWidgets {

    class HudWidgetImageData : public HudWidget {
    public:
        HudWidgetImageData(Images::ImageData image, int yCoordinate);

        void init(HudDisplay *_disp, std::function<int(void)> _dataFetcher) {
          HudWidget::init(_disp);
          this->dataFetcher = std::move(_dataFetcher);
        };

        void draw(bool force) ;

    private:
        Images::ImageData image; // The image to display

        std::function<int(void)> dataFetcher;
        int lastData = -1091001; // The last data value we displayed (set something it will never be on start)
    };

} // HudWidgets

#endif //LASERTAG_HUDWIDGETIMAGEDATA_H
