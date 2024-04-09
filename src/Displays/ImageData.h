/*
  Created by Ed Fillingham on 09/04/2024.

  This contains a struct to describe an image and then includes
  all images that will be used in the project.
*/

#ifndef LASERTAG_IMAGEDATA_H
#define LASERTAG_IMAGEDATA_H

namespace ImageData {

    struct ImageData {
        int width;
        int height;
        const unsigned char *MyImage; // Pointer to const unsigned char
    };


// include all images here

#include "Displays/Images/img_Bullet.h"

}
#endif //LASERTAG_IMAGEDATA_H
