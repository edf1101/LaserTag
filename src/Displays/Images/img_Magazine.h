/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is a bullet image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_MAGAZINE_H
#define LASERTAG_IMG_MAGAZINE_H

# include <Arduino.h>
# include "../ImageData.h"


// put image here
// 'mag', 15x18px
const unsigned char epd_bitmap_mag[] PROGMEM = {
        0x00, 0x00, 0x1f, 0xe0, 0x1b, 0x60, 0x1f, 0x60, 0x1b, 0x60, 0x0b, 0x70, 0x0b, 0x70, 0x0f, 0xf0,
        0x0f, 0xf0, 0x1b, 0x70, 0x1b, 0x60, 0x1f, 0x60, 0x17, 0xe0, 0x36, 0xc0, 0x6d, 0x80, 0x7b, 0x80,
        0x3f, 0x00, 0x00, 0x00
};

// put the image in a struct here
const ImageData img_mag = {
        15, // width of image
        18, // height of image
        epd_bitmap_mag // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_MAGAZINE_H
