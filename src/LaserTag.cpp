/*
 * Created by Ed Fillingham on 09/04/2024.
 *
 * This class controls and holds all logic & variables for the entire gun / game.
 * The main.cpp or .ino file just calls this class' void init() instead of void setup()
 * and this class' void loop().
*/

#include "LaserTag.h"

void LaserTag::init() {
  // This gets called once at the start of the program

  Serial.begin(9600); // start serial communication for debug purposes
  hudDisplay.init();
  sideDisplay.init();
}

void LaserTag::loop() {
  // This gets called everytime the loop() function is called in the main.cpp / LaserTag.ino file

  sideDisplay.pollEncoder();
}
