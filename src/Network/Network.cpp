/*
 * Created by Ed Fillingham on 20/04/2024.
*/

#include "Network.h"

namespace Networks {


    void Network::init() {
      // set up the network class

      meshManager.init();

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

    void Network::loop() {
      // update the network

      meshManager.loop();
    }

    void Network::disconnectNetwork(){
      // disconnect from the network

      meshManager.disconnect();

    }
} // Networks