/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is an image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_MENUNAME_H
#define LASERTAG_IMG_MENUNAME_H

# include <Arduino.h>
# include "../ImageData.h"


// put image here
// 'menuName', 36x31px
const unsigned char epd_bitmap_menuName [] PROGMEM = {
        0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0f,
        0x87, 0xf0, 0x1c, 0x00, 0x3f, 0xe7, 0xf8, 0x7f, 0x00, 0x3f, 0xe7, 0xfc, 0xff, 0x80, 0x38, 0xe7,
        0x9e, 0xe3, 0x80, 0x31, 0xe7, 0x0e, 0xe1, 0x80, 0x1f, 0xe7, 0x0e, 0xc0, 0x00, 0x3f, 0xe7, 0x0e,
        0xc0, 0x00, 0x7c, 0xe7, 0x0e, 0xe1, 0xc0, 0x70, 0xe7, 0x1e, 0xe3, 0x80, 0x7f, 0xe7, 0xfc, 0xff,
        0x80, 0x3f, 0xf7, 0xfc, 0x7f, 0x80, 0x1f, 0x77, 0xf0, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00,
        0x00, 0xe0, 0x00, 0x7c, 0x00, 0x00, 0xe0, 0x00, 0x7c, 0x00, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0x07,
        0xe0, 0xf1, 0xf8, 0x00, 0x1f, 0xe3, 0xf9, 0xf8, 0x00, 0x3f, 0xe7, 0xfd, 0xf8, 0x00, 0x38, 0xe7,
        0x1e, 0xe0, 0x00, 0x70, 0xe7, 0x0e, 0xe0, 0x00, 0x70, 0xef, 0xfe, 0xe0, 0x00, 0x70, 0xef, 0xfe,
        0xe0, 0x00, 0x70, 0xee, 0x08, 0xe0, 0x00, 0x38, 0xe7, 0x1e, 0xe0, 0x00, 0x3f, 0xe7, 0xfe, 0xe0,
        0x00, 0x1f, 0xe3, 0xfc, 0xe0, 0x00, 0x0f, 0xe1, 0xf8, 0xe0, 0x00
};

// put the image in a struct here
const ImageData img_menuName = {
        36, // width of image
        31, // height of image
        epd_bitmap_menuName // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_MENUNAME_H
