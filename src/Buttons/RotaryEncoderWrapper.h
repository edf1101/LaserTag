/*
 * Created by Ed Fillingham on 05/07/2024.
*/

#ifndef LASERTAG_ROTARYENCODERWRAPPER_H
#define LASERTAG_ROTARYENCODERWRAPPER_H

#include "Arduino.h"
#include "Libs/ESP32Encoder/ESP32Encoder.h"
#include <functional>

class RotaryEncoderWrapper {
public:
    RotaryEncoderWrapper(uint8_t inputA, uint8_t inputB); // constructor for the RotaryEncoderWrapper class

    void setCallbackFunc(std::function<void(long)> changeCallback); // set the callback function
    unsigned long getLastActivity() const;

    void poll(); // poll the rotary encoder for changes

private:
ESP32Encoder myEncoder;

    std::function<void(long)> realCallbackFunc;
    bool callbackFuncSet = false;

    void callCallbackFunc(long value);

    unsigned long lastActivity = 0; // The last time the rotary encoder was turned

    int64_t lastCount = 0; // The last count of the rotary encoder
};


#endif //LASERTAG_ROTARYENCODERWRAPPER_H
