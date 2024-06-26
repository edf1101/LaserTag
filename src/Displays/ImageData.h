/*
  Created by Ed Fillingham on 09/04/2024.

  This contains a struct to describe an image and then includes
  all images that will be used in the project.
*/

#ifndef LASERTAG_IMAGEDATA_H
#define LASERTAG_IMAGEDATA_H

#include "Arduino.h"

namespace Images {

    struct ImageData {
        int width;
        int height;
        const unsigned char *MyImage; // Pointer to const unsigned char
    };

    // Describes how we want an image to be centered / or not when drawing it
    enum OFFSET{
        TOP_LEFT,
        CENTERED,
    };

// include all images here

#include "Images/img_Bullet.h"
#include "Images/img_Revive.h"
#include "Images/img_Heart.h"
#include "Images/img_Magazine.h"
#include "Images/img_DeadRevive.h"
#include "Images/img_menuAdmin.h"
#include "Images/img_menuGun.h"
#include "Images/img_MenuLeaderboard.h"
#include "Images/img_menuSettings.h"
#include "Images/img_menuMessages.h"
#include "Images/img_menuName.h"
#include "Images/img_menuTurnOff.h"
#include "Images/img_menuReturn.h"
#include "Images/img_LeftArrow.h"
#include "Images/img_RightArrow.h"
#include "Images/img_subMenuReturn.h"
#include "Images/img_subMenuSelect.h"
#include "Images/img_gunAR.h"
#include "Images/img_gunShotgun.h"
#include "Images/img_gunSniper.h"
#include "Images/img_gunPistol.h"
#include "Images/img_gunPisSup.h"
#include "Images/img_gunMAC11.h"
#include "Images/img_menuCommand.h"


}
#endif //LASERTAG_IMAGEDATA_H
