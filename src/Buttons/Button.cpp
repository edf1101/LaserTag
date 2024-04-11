/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class represents a single button and has callbacks
 * for when the button is pressed and released.
*/

#include "Button.h"

#include <utility>

Button::Button(int pin) {
  // Constructor for the Button class
  this->pin = pin;
  pinMode(pin, INPUT_PULLDOWN);
}

void Button::SetPressedCallback(std::function<void(void)> callback) {
  // Set the callback function for when the button is pressed
  this->pressedCallback = std::move(callback);
  this->setPressedCallback = true;
}

void Button::SetReleasedCallback(std::function<void(void)> callback) {
  // Set the callback function for when the button is released
  this->releasedCallback = std::move(callback);
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