/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is a bullet image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_INFINITY_H
#define LASERTAG_IMG_INFINITY_H

# include <Arduino.h>
# include "Hardware/Displays/ImageData.h"


// put image here
// 'infinity', 15x18px
const unsigned char epd_bitmap_infinity [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x7e, 0xfc, 0xe7, 0xce,
        0xc3, 0x86, 0xc3, 0x86, 0xc3, 0x86, 0xe7, 0xce, 0x7e, 0xfc, 0x3c, 0x78, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
};

// put the image in a struct here
const ImageData img_infinity = {
        15, // width of image
        18, // height of image
        epd_bitmap_infinity // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_INFINITY_H
