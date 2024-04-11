/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This class represents a single button and has callbacks
 * for when the button is pressed and released.
*/

#ifndef LASERTAG_BUTTON_H
#define LASERTAG_BUTTON_H

#include "Arduino.h"


class Button {
public:
    explicit Button(int pin);

    void SetPressedCallback(void (*_pressedCallback)());

    void SetReleasedCallback(void (*_releasedCallback)());

    void poll();

    bool isPressed() const;

private:
    int pin;
    bool lastState = false;

    void (*pressedCallback)();

    bool setPressedCallback = false;

    void (*releasedCallback)();

    bool setReleasedCallback = false;

};


#endif //LASERTAG_BUTTON_H
