/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is a bullet image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_REVIVE_H
#define LASERTAG_IMG_REVIVE_H

# include <Arduino.h>
# include "Hardware/Displays/ImageData.h"


// put image here
const unsigned char epd_bitmap_revive[] PROGMEM = {
        0x0f, 0xe0, 0x0f, 0xe0, 0x02, 0x80, 0x02, 0x80, 0x3f, 0xf8, 0x3f, 0xf8, 0x08, 0x20, 0x0e, 0x20,
        0x08, 0x20, 0x0e, 0x20, 0x08, 0x60, 0x09, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x02, 0x80,
        0x02, 0x80, 0x03, 0x80
};

// put the image in a struct here
const ImageData img_revive = {
        15, // width of image
        18, // height of image
        epd_bitmap_revive // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_REVIVe_H
