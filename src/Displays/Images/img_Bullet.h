/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is a bullet image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_BULLET_H
#define LASERTAG_IMG_BULLET_H

# include <Arduino.h>
# include "../ImageData.h"


// put image here
const unsigned char epd_bitmap_bullet[] PROGMEM = {
        0x01, 0x00, 0x03, 0x80, 0x06, 0xc0, 0x04, 0x40, 0x0c, 0x60, 0x08, 0x20, 0x0f, 0xe0, 0x0f, 0xe0,
        0x0b, 0xe0, 0x0b, 0xe0, 0x0b, 0xe0, 0x0b, 0xe0, 0x0b, 0xe0, 0x0b, 0xe0, 0x0b, 0xe0, 0x0f, 0xe0,
        0x00, 0x00, 0x00, 0x00
};

// put the image in a struct here
const ImageData img_bullet = {
        15, // width of image
        18, // height of image
        epd_bitmap_bullet // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_BULLET_H
