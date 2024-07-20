/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class represents a single button and has callbacks
 * for when the button is pressed and released.
*/

#include "Button.h"

#include <utility>

Button::Button(int pin, uint8_t inputMode, bool extendedGPIO) {
  // Constructor for the Button class
  this->pin = pin;
  this->inputMode = inputMode;
  this->extendedGPIO = extendedGPIO;

  // Set the pin mode using diff functions depending on if we are using extended GPIO or not
  if (extendedGPIO) {
    Hardware::pinModeExp(pin, inputMode);
  } else {
    pinMode(pin, inputMode);
  }

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

  // read the pin mode using diff functions depending on if we are using extended GPIO or not
  bool currentState;
  if (extendedGPIO) {
    currentState = Hardware::digitalReadExp(pin);
  } else {
    currentState = digitalRead(pin);
  }

  if (inputMode == INPUT_PULLUP) {
    currentState = !currentState;
  }

  if (currentState != lastState) {
    lastState = currentState;
    lastActivity = millis();
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

  bool currentState;
  if (extendedGPIO) {
    currentState = Hardware::digitalReadExp(pin);
  } else {
    currentState = digitalRead(pin);
  }

  if (inputMode == INPUT_PULLUP) { // If the button is a pullup, invert the logic
    return currentState == LOW;
  }
  return currentState == HIGH;
}

unsigned long Button::getLastActivity() const {
  // Return the last time the button was pressed or released

  return lastActivity;
}
