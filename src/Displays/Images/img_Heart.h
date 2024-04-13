/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is a bullet image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_HEART_H
#define LASERTAG_IMG_HEART_H

# include <Arduino.h>
# include "../ImageData.h"


// put image here
// 'heart', 15x18px
const unsigned char epd_bitmap_heart[] PROGMEM = {
        0x1c, 0x70, 0x3e, 0xf8, 0x3f, 0xf8, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc,
        0x3f, 0xfc, 0x3f, 0xf8, 0x3f, 0xf8, 0x1f, 0xf0, 0x1f, 0xf0, 0x0f, 0xe0, 0x0f, 0xe0, 0x07, 0xc0,
        0x07, 0xc0, 0x03, 0x80
};

// put the image in a struct here
const ImageData img_heart = {
        15, // width of image
        18, // height of image
        epd_bitmap_heart // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_HEART_H
