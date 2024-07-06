/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class represents a single button and has callbacks
 * for when the button is pressed and released.
*/

#ifndef LASERTAG_BUTTON_H
#define LASERTAG_BUTTON_H

#include "Arduino.h"
#include <functional>


class Button {
public:
    explicit Button(int pin, uint8_t inputMode = INPUT_PULLDOWN);

    void SetPressedCallback(std::function<void(void)> callback);

    void SetReleasedCallback(std::function<void(void)> callback);

    void poll();

    bool isPressed() const;

    unsigned long getLastActivity() const;

private:
    int pin;
    uint8_t inputMode;
    bool lastState = false;

    std::function<void(void)> pressedCallback;

    bool setPressedCallback = false;

    std::function<void(void)> releasedCallback;

    bool setReleasedCallback = false;

    unsigned long lastActivity = 0; // The last time the button was pressed or released

};


#endif //LASERTAG_BUTTON_H
