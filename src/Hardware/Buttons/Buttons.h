/*
 * Created by Ed Fillingham on 11/04/2024.
 *
 * This references all the buttons on the gun used in the project.
*/

#ifndef LASERTAG_BUTTONS_H
#define LASERTAG_BUTTONS_H

#include "Button.h"
#include "RotaryEncoderWrapper.h"
#include "Arduino.h"
#include "../../config.h"


class Buttons {
public:
    Button triggerButton = Button(TRIGGER_BUTTON);
    Button magazineButton = Button(MAGAZINE_BUTTON, INPUT_PULLDOWN);

    Button rotaryButton = Button(ROT_SWITCH, INPUT_PULLDOWN);
    RotaryEncoderWrapper rotaryEncoder = RotaryEncoderWrapper(ROT_OUT_A, ROT_OUT_B);

    void pollButtons() {
      // Polls all the buttons for updates
      triggerButton.poll();
      magazineButton.poll();
      rotaryButton.poll();
      rotaryEncoder.poll();
    }

    unsigned long getLastActivity() const {
      // Returns the last time any button was pressed or released

      unsigned long lastActivity = 0;

      // For each button max it with the last activity here.
      lastActivity = max(lastActivity, triggerButton.getLastActivity());
      lastActivity = max(lastActivity, magazineButton.getLastActivity());
      lastActivity = max(lastActivity, rotaryButton.getLastActivity());
      lastActivity = max(lastActivity, rotaryEncoder.getLastActivity());

      return lastActivity;
    }
};


#endif //LASERTAG_BUTTONS_H
