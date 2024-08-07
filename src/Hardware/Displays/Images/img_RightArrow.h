/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is an image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_RIGHTARROW_H
#define LASERTAG_IMG_RIGHTARROW_H

# include <Arduino.h>
# include "Hardware/Displays/ImageData.h"


// put image here
// 'right arrow', 30x30px
const unsigned char epd_bitmap_right_arrow [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
        0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1f, 0x00,
        0x0f, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0,
        0x0f, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1e, 0x00,
        0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// put the image in a struct here
const ImageData img_rightArrow = {
        30, // width of image
        30, // height of image
        epd_bitmap_right_arrow // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_RIGHTARROW_H
