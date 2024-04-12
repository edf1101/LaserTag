/*
 * Created by Ed Fillingham on 12/04/2024.
*/

#ifndef FIRING_CPP_GAMEMODESOLO_H
#define FIRING_CPP_GAMEMODESOLO_H

#include "Gamemode.h"
#include <string>

class GamemodeSolo : public Gamemode{
public:
  GamemodeSolo(LaserTag* _mySystem) : Gamemode(_mySystem) {
    name = "Solo Free for All";
    teamBased = false;
    playerStartingRevives = 3;
  }
protected:

};


#endif //FIRING_CPP_GAMEMODESOLO_H
