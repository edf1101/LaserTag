/*
 * Created by Ed Fillingham on 05/07/2024.
*/

#include "RotaryEncoderWrapper.h"

#include <utility>

RotaryEncoderWrapper::RotaryEncoderWrapper(uint8_t inputA, uint8_t inputB) {
// constructor for the RotaryEncoderWrapper class

  myEncoder.attachHalfQuad(inputA, inputB);
}

void RotaryEncoderWrapper::callCallbackFunc(long value) {
  // call the callback function

  if (callbackFuncSet) {
    lastActivity = millis(); // set the last activity time
    realCallbackFunc(value);
  }
}

unsigned long RotaryEncoderWrapper::getLastActivity() const {
  return lastActivity;
}

void RotaryEncoderWrapper::setCallbackFunc(std::function<void(long)> changeCallback) {
  // set the callback function

  callbackFuncSet = true;
  realCallbackFunc = std::move(changeCallback);
}

void RotaryEncoderWrapper::poll() {
  // poll the rotary encoder for changes

  int64_t count = myEncoder.getCount();
  int diff = (int)(lastCount - count);
  if (abs(diff) >= 2) {
    lastCount = count;
    diff /= 2;

    callCallbackFunc(diff);
    lastActivity = millis();
  }
}

