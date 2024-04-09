/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class controls and holds all logic & variables for the entire gun / game.
 * The main.cpp or .ino file just calls this class' void init() instead of void setup()
 * and this class' void loop().
*/

#ifndef LASERTAG_LASERTAG_H
#define LASERTAG_LASERTAG_H

#include "Displays/HudDisplay.h"
#include "Displays/SideDisplay.h"


class LaserTag {
public :
    void init();
    void loop();
private:
    HudDisplay hudDisplay;  // display objects
    SideDisplay sideDisplay;

};


#endif //LASERTAG_LASERTAG_H