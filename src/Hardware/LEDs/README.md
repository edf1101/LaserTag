# /LEDs

This folder contains The LED manager script and the NEOPIXEL LED effects inside the ./Effects folder.

## Creating new effects
Create a class within the effects folder, This class must inherit from LEDEffect.
It must have two functions:
- A constructor to set up effect length etc
- updateLEDs(): which is where you draw to the LED strip

You can then include the new class' header file inside AllLEDEffects.h so it can be accessed anywhere LEDs are used.
