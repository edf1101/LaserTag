/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This header file holds references to all the weapons in the game. You add new weapons here.
*/

#ifndef LASERTAG_WEAPONS_H
#define LASERTAG_WEAPONS_H

#include "Arduino.h"
#include <string>
#include "Gun.h" // For creating Gun types
#include "Displays/ImageData.h" // For getting gun images

namespace Weapons {


    const Weapons::Gun AssaultRifle = Weapons::Gun(0, "Assault Rifle", "AR", Images::img_bullet,
                                                   16, 10, 2000,
                                                   Weapons::ReloadType::PRESS_ALL, 20,
                                                   200, 100, 400,
                                                   -1, false, 1);


}

#endif //LASERTAG_WEAPONS_H
