/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This class handles the network functionality of the gun.
*/

#include "Network.h"

#include <utility>
#include "../LaserTag.h"

namespace Networks {


    void Network::init() {
      // set up the network class

      meshManager.init();

      adminStatus = false;
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

        // tell the msg queue we joined the lobby
        LaserTag::getNetworkManager()->getMessageQueue()->pushMessage("Joined Lobby as admin");
      }
    }

    void Network::loop() {
      // update the network

      meshManager.loop();

      if (!inLobby &&
          millis() - lastJoinRequestSent > 2000 + random(1, 200)) { // + random to avoid consistent collisions
        // If we are not in the lobby and we haven't sent a join request in the last 5 seconds
        // Send a join request
        lastJoinRequestSent = millis();
        meshManager.sendJoinRequest();
      }

      if (inLobby &&
          millis() - lastStatusUpdateSent > 5000 + random(1, 200)) { // + random to avoid consistent collisions
        // If we are in the lobby and we haven't sent a status update in the last second
        // Send a status update
        lastStatusUpdateSent = millis();
        meshManager.sendUpdate();
      }

    }

    void Network::disconnectNetwork() {
      // disconnect from the network
      // TODO if you turn off your gun u lose all lives so you can't benefit from this.
      meshManager.disconnect();

    }

    void Network::joinLobby(Player myPlayerTemplate) {
      // join the lobby

      inLobby = true;
      Serial.println("Joined lobby");

      LaserTag::getNetworkManager()->getMessageQueue()->pushMessage(
              "Joined Lobby"); // tell the msg queue we joined the lobby

      LaserTag::getGamemode()->drawHUD(); // so it says we're in a lobby now.

      PlayerWrapper *myPlayer = LaserTag::getPlayer();
      myPlayer->setPlayerToTemplate(myPlayerTemplate);
      myPlayer->setUnitnum(myPlayerTemplate.unitnum);
      myPlayer->setName(myPlayerTemplate.name);

    }

    void Network::setPlayerInMap(uint32_t id, Player player) {
      // Add a player to the map

      playersMap[id] = std::move(player);

      // while we do this update the unitnum in the unitnum to node id map
      int playerUnitnum = playersMap[id].unitnum;
      unitnumToNodeIDMap[playerUnitnum] = id;
    }

    Player *Network::getPlayerInMap(uint32_t id) {
      // Get a player from the map

      return &playersMap[id];
    }

    uint32_t Network::getPlayerIdByUnitnum(int unitnum) {
      // Get a node ID for a laser tagger from the map by its unitnum

      if (unitnumToNodeIDMap.find(unitnum) != unitnumToNodeIDMap.end()) {
        return unitnumToNodeIDMap[unitnum];
      } else {
        return -1;
      }
    }

    Player *Network::getPlayerByUnitnum(int unitnum) {
      // Get a player from the map by its unitnum

      vector<uint32_t> allPlayers = getAllPlayerNodeIDs();

      for (uint32_t playerID: allPlayers) {
        if (playersMap[playerID].unitnum == unitnum) {
          return &playersMap[playerID];
        }
      }
      return nullptr;
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

    void Network::sendHitConfirmation(int shooterUnitnum, int vicitmUnitnum, bool killConfirm) {
      // send a hit / kill confirmation. This is a wrapper for the mesh manager send hit conf function,
      // needed as mesh manager is private.

      meshManager.sendHitConfirmation(shooterUnitnum, vicitmUnitnum, killConfirm);
    }

    void Network::handleHitConfirmation(int shooterUnitnum, int victimUnitnum, bool killConfirm) {
      // when we get a hit confirmation from the network we handle it.
      // it gets handles here as meshmanager is more low level

      Serial.println("Hit confirmation received format: Killer,Victim,died(bool) " + String(shooterUnitnum) + "," +
                     String(victimUnitnum) + "," + String(killConfirm));

      std::string shooterName = LaserTag::getNetworkManager()->getPlayerByUnitnum(shooterUnitnum)->name;
      std::string victimName = LaserTag::getNetworkManager()->getPlayerByUnitnum(victimUnitnum)->name;

      if (killConfirm) { // If the victim died put that on our message queue.
        messageQueue.pushMessage(shooterName + " killed " + victimName + " " + +"!");
      }

      if (shooterUnitnum ==
          LaserTag::getPlayer()->getUnitnum()) { // If we are the shooter let the game know we hit someone.

        LaserTag::getGamemodeManager()->getCurrentGame()->onHitConfirm(victimUnitnum, killConfirm);
      }
    }

    set<uint32_t> Network::getActivePlayers() {
      // return all active players. This is a wrapper for the mesh manager get active nodes function,

      return meshManager.getActiveNodes();
    }

} // Networks