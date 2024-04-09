#include <Arduino.h>
#include "Displays/HudDisplay.h"
HudDisplay hud;

void setup() {
    // Gets called once at the start of the program
    hud.init();
}

void loop() {
    // Gets called repeatedly by the microcontroller
}
