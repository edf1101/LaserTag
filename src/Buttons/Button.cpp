/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class represents a single button and has callbacks
 * for when the button is pressed and released.
*/

#include "Button.h"

Button::Button(int pin) {
  // Constructor for the Button class
  this->pin = pin;
  pinMode(pin, INPUT);
}

void Button::SetPressedCallback(void (*_pressedCallback)()) {
  // Set the callback function for when the button is pressed
  this->pressedCallback = _pressedCallback;
  this->setPressedCallback = true;
}

void Button::SetReleasedCallback(void (*_releasedCallback)()) {
  // Set the callback function for when the button is released
  this->releasedCallback = _releasedCallback;
  this->setReleasedCallback = true;
}

void Button::poll() {
  // Poll the button to see if it has been pressed or released
  bool currentState = digitalRead(pin);

  if (currentState != lastState) {
    lastState = currentState;
    if (currentState == HIGH) {

      if (setPressedCallback) {
        pressedCallback();
      }
    } else {
      if (setReleasedCallback) {
        releasedCallback();
      }
    }
  }
}

bool Button::isPressed() const {
  // Return whether the button is currently pressed
  return digitalRead(pin) == HIGH;
}