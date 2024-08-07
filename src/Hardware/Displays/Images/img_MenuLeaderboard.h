/*
 * Created by Ed Fillingham on 08/04/2024.
 *
 *  This is an image file that will be displayed on the OLED HUD (heads up display)
*/

#ifndef LASERTAG_IMG_MENULEADERBOARD_H
#define LASERTAG_IMG_MENULEADERBOARD_H

# include <Arduino.h>
# include "Hardware/Displays/ImageData.h"


// put image here
// 'menuLeaderboard', 36x31px
const unsigned char epd_bitmap_menuLeaderboard [] PROGMEM = {
        0x0c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c,
        0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x33,
        0x30, 0x00, 0x00, 0x0c, 0x33, 0x30, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff,
        0xff, 0xf0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00,
        0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00,
        0x3c, 0x00, 0x00, 0x00, 0x00, 0x78, 0x33, 0x30, 0x00, 0x00, 0x7f, 0x33, 0x30, 0x00, 0x00, 0x7f,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00,
        0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00,
        0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x77, 0x33, 0x30, 0x00,
        0x00, 0x3e, 0x33, 0x30, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00
};

// put the image in a struct here
const ImageData img_menuLeaderboard = {
        36, // width of image
        31, // height of image
        epd_bitmap_menuLeaderboard // Assign the address of bulletImg
};


#endif //LASERTAG_IMG_MENULEADERBOARD_H
