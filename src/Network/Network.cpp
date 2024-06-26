/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This class handles the network functionality of the gun.
*/

#include "Network.h"
#include "LaserTag.h"

namespace Networks {


    void Network::init() {
      // set up the network class

      meshManager.init();

      adminStatus = false;

      // Set up the message Queue
      for (int i = 0; i < 16; i++) {
        messageQueue.pushMessage("Msg " + std::to_string(i));
        debugMessageQueue.pushMessage("");
      }

    }

    void Network::tryMakeAdmin(std::string adminCode) {
      // check if the admin code is correct

      if (adminCode == ADMIN_PASS) {
        Serial.println("Admin status granted");
        adminStatus = true;
        inLobby = true; // If we are the admin we are automatically in the lobby
      }
    }

    void Network::loop() {
      // update the network

      meshManager.loop();

      if (!inLobby && millis() - lastJoinRequestSent > 2000 + random(1, 200)) { // +random to avoid collisions
        // If we are not in the lobby and we haven't sent a join request in the last 5 seconds
        // Send a join request
        lastJoinRequestSent = millis();
        meshManager.sendJoinRequest();
      }
    }

    void Network::disconnectNetwork() {
      // disconnect from the network

      meshManager.disconnect();

    }

    void Network::joinLobby(bool alreadyInGame, Player *myPlayer) {
      // join the lobby

      inLobby = true;
      Serial.println("Joined lobby");
      LaserTag::getGamemode()->drawHUD();

    }
} // Networks