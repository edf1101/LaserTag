/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This class handles the network functionality of the gun.
*/

#include "Network.h"

#include <utility>
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

        // reset my player to be the default gamemode player
        Player playerTemplate = LaserTag::getGamemodeManager()->getCurrentGame()->getPlayerTemplate();
        LaserTag::getPlayer()->setPlayerToTemplate(playerTemplate);
      }
    }

    void Network::loop() {
      // update the network

      meshManager.loop();

      if (!inLobby && millis() - lastJoinRequestSent > 2000 + random(1, 200)) { // + random to avoid consistent collisions
        // If we are not in the lobby and we haven't sent a join request in the last 5 seconds
        // Send a join request
        lastJoinRequestSent = millis();
        meshManager.sendJoinRequest();
      }

      if (inLobby && millis() - lastStatusUpdateSent > 5000 + random(1, 200)) { // + random to avoid consistent collisions
        // If we are in the lobby and we haven't sent a status update in the last second
        // Send a status update
        lastStatusUpdateSent = millis();
        meshManager.sendUpdate();
      }

    }

    void Network::disconnectNetwork() {
      // disconnect from the network

      meshManager.disconnect();

    }

    void Network::joinLobby( Player myPlayerTemplate) {
      // join the lobby

      inLobby = true;
      Serial.println("Joined lobby");
      LaserTag::getGamemode()->drawHUD();

      PlayerWrapper* myPlayer = LaserTag::getPlayer();
      myPlayer->setPlayerToTemplate(myPlayerTemplate);
      myPlayer->setUnitnum(myPlayerTemplate.unitnum);
      myPlayer->setName(myPlayerTemplate.name);

    }

    void Network::setPlayerInMap(uint32_t id, Player player) {
      // Add a player to the map

      playersMap[id] = std::move(player);
    }

    Player *Network::getPlayerInMap(uint32_t id) {
      // Get a player from the map

      return &playersMap[id];
    }

    vector<uint32_t> Network::getAllPlayerNodeIDs() {
      // Returns all the players (keys) in the player map

      std::vector<uint32_t> players;
      for (auto const &x: playersMap) {
        players.push_back(x.first);
      }

      return players;
    }

    void Network::sendCommand(std::string commandCode) {
      // send a command. This is a wrapper for the mesh manager send command function,
      // needed as mesh manager is private.

      meshManager.sendCommand(commandCode);
    }

    void Network::loadGamemodeDetails(JsonObject gameData) {
      // load into a gamemode according to network data details

      int gamemodeIndex = gameData["gamemodeIndex"];
      LaserTag::getGamemodeManager()->switchGamemodeByInt(gamemodeIndex);
      LaserTag::getGamemodeManager()->getCurrentGame()->loadGameDetails(gameData);



    }

} // Networks