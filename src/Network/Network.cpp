/*
 * Created by Ed Fillingham on 20/04/2024.
*/

#include "Network.h"

namespace Networks {


    void Network::init() {
      // set up the network class

      adminStatus = false;

      // Set up the message Queue
      for (int i = 0; i < 16; i++) {
        messageQueue.pushMessage("");
      }

    }

    void Network::tryMakeAdmin(std::string adminCode) {
      // check if the admin code is correct

      if (adminCode == ADMIN_PASS) {
        Serial.println("Admin status granted");
        adminStatus = true;
      }
    }
} // Networks