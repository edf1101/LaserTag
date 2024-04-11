/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This references all the buttons on the gun used in the project.
*/

#ifndef LASERTAG_BUTTONS_H
#define LASERTAG_BUTTONS_H

#include "Button.h"
#include "../Pins.h"


class Buttons {
public:
    Button triggerButton = Button(TRIGGER_BUTTON);

    void pollButtons() {
      // Polls all the buttons for updates
      triggerButton.poll();
    }
};


#endif //LASERTAG_BUTTONS_H
