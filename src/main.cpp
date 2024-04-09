#include <Arduino.h>
#include "Displays/HudDisplay.h"
#include "Displays/SideDisplay.h"
HudDisplay hud;
SideDisplay sideDisplay;

void setup() {
    // Gets called once at the start of the program
    Serial.begin(9600);
    hud.init();
    sideDisplay.init();
}

void loop() {
    // Gets called repeatedly by the microcontroller
    sideDisplay.pollEncoder();
}
