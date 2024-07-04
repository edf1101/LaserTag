/*
 * Created by Ed Fillingham on 22/04/2024.
 *
 * This file manages, sends and receives messages on the mesh network.
*/

#include "MeshManager.h"
#include "Network.h"
#include "../Commands/Command.h"
#include "../LaserTag.h"

namespace Networks {
    void MeshManager::init() {
      mesh.setDebugMsgTypes(ERROR | STARTUP);  // set before init() so that you can see startup messages

      mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
      mesh.onReceive(std::bind(&MeshManager::receivedCallback, this, std::placeholders::_1, std::placeholders::_2));
      mesh.onNewConnection(std::bind(&MeshManager::newConnectionCallback, this, std::placeholders::_1));
      mesh.onChangedConnections(std::bind(&MeshManager::changedConnectionCallback, this));
      mesh.onNodeTimeAdjusted(std::bind(&MeshManager::nodeTimeAdjustedCallback, this, std::placeholders::_1));

    }

    void MeshManager::disconnect() {
      // disconnect from the network

      mesh.stop();
    }

    void MeshManager::loop() {
      // update the mesh
      mesh.update();

    }


// Needed for painless library
    void MeshManager::receivedCallback(uint32_t from, String &msg) {
      // When a message is received this callback function is called

#if DEBUG_SERIAL
      Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
#endif

      // Parse the JSON message
      JsonDocument jsonIn;
      deserializeJson(jsonIn, msg);

      byte control = jsonIn["control"];
      if (control == ControlTypes::COMMAND) {
        // Do something on received command
        std::string commandCode = jsonIn["code"]; // get the command code from the JSON message

        if (!Commands::Command::commandExists(commandCode)) { return; } // if command doesn't exist return

        // It must exist now so get the command
        Commands::Command *command = Commands::Command::getCommandByCode(commandCode);

        LaserTag::getCommandManager()->processCommand(command); // process the command

      } else if (control == ControlTypes::HIT_CONFIRM) {
        // Do something on received kill confirm

        int shooterUnitnum = jsonIn["data"]["shooterUnitnum"];
        int victimUnitnum = jsonIn["data"]["victimUnitnum"];
        bool killConfirm = jsonIn["data"]["killConfirm"];
        LaserTag::getNetworkManager()->handleHitConfirmation(shooterUnitnum, victimUnitnum, killConfirm);

      } else if (control == ControlTypes::UPDATE) {
        // Do something on received update

        handleUpdateRx(from, msg);

      } else if (control == ControlTypes::JOIN) {
        // Do something on received join game command

        if (!Network::getAdminStatus()) {
          // If not the admin return and do nothing
          return;
        }
        handleLobbyJoinRequest(from);

      } else if (control == ControlTypes::JOIN_ACKNOWLEDGE) {
        // Do something on received join acknowledge
        handleJoinLobbyAck(msg);
      }
    }

    void MeshManager::handleJoinLobbyAck(String jsonData) {
      // Handle a join acknowledge message

      JsonDocument jsonIn; // deserialize the json message
      deserializeJson(jsonIn, jsonData);

      if ((JoinAckStates) jsonIn["joinState"] == JoinAckStates::ACCEPT_NEW_GUN) {
        // If the join was accepted and the node is a new gun

        int newUnitnum = jsonIn["unitnum"];
        std::string newName = jsonIn["name"];

        JsonObject gamemodeData = jsonIn["gamemodeData"];
        // switch gamemodes before we load the gamemodes default player struct
        LaserTag::getNetworkManager()->loadGamemodeDetails(gamemodeData);

        // get the default gamemode player struct and add a new unitnum to it
        Player playerTemplate = LaserTag::getGamemodeManager()->getCurrentGame()->getPlayerTemplate();
        playerTemplate.unitnum = newUnitnum;
        playerTemplate.name = newName;

        Network::joinLobby(playerTemplate);

      } else if ((JoinAckStates) jsonIn["joinState"] == JoinAckStates::ACCEPT_EXISTING_GUN) {
        // If the join was accepted and the node is an existing gun

        JsonObject gamemodeData = jsonIn["gamemodeData"];
        // switch gamemodes before we load the player struct
        LaserTag::getNetworkManager()->loadGamemodeDetails(gamemodeData);

        // get the existing player's details from the JSON data
        Player existingPlayer = {
                jsonIn["data"]["unitnum"],
                jsonIn["data"]["team"],
                jsonIn["data"]["name"],
                jsonIn["data"]["revives"],
                jsonIn["data"]["health"],
                jsonIn["data"]["kills"],
                false,
                0
        };

        Network::joinLobby(existingPlayer);

      }

    }

    void MeshManager::sendJoinRequest() {
      // Send a join request to the network

      JsonDocument jsonOut;
      jsonOut["control"] = ControlTypes::JOIN;
      String msg = "";
      serializeJson(jsonOut, msg);
      mesh.sendBroadcast(msg);
    }

    void MeshManager::handleLobbyJoinRequest(uint32_t from) {
      // Handle a join request from a node

      JsonDocument jsonOut;
      jsonOut["control"] = ControlTypes::JOIN_ACKNOWLEDGE;
      Serial.println("Handling join request");
      // Check if the node is already in the game
      if (connectedNodes.find(from) != connectedNodes.end()) {
        Serial.println("Node is already in the lobby");
        // If the node is already in the game find it's stats and send them back to make the node rejoin in last state.
        // This is useful if the node has been disconnected and reconnected and needs to rejoin the game

        Player *existingPlayer = LaserTag::getNetworkManager()->getPlayerInMap(from); // get the existing player
        jsonOut["data"]["unitnum"] = existingPlayer->unitnum;
        jsonOut["data"]["team"] = existingPlayer->team;
        jsonOut["data"]["name"] = existingPlayer->name;
        jsonOut["data"]["revives"] = existingPlayer->revives;
        jsonOut["data"]["health"] = existingPlayer->health;
        jsonOut["data"]["kills"] = existingPlayer->name;

        jsonOut["joinState"] = JoinAckStates::ACCEPT_EXISTING_GUN;

      } else {
        // If the node is not in the game add it to the game
        connectedNodes.insert(from);

        // pick a unitnum for the node
        // TODO implement this properly
        int unitnum = random(1, 127);
        Serial.println("Node is new, Assigning it unitnum: " + String(unitnum));
        jsonOut["unitnum"] = unitnum;
        jsonOut["name"] = "Player" + String(unitnum);
        jsonOut["joinState"] = JoinAckStates::ACCEPT_NEW_GUN;

        // add it to the network map of players
        Player newPlayer = LaserTag::getGamemodeManager()->getCurrentGame()->getPlayerTemplate();
        newPlayer.unitnum = unitnum;
        newPlayer.name = "Player" + std::to_string(unitnum);
        LaserTag::getNetworkManager()->setPlayerInMap(from, newPlayer);
      }

      // Add in the gamemode data to the JSON object
      jsonOut["gamemodeData"] = LaserTag::getGamemodeManager()->getCurrentGame()->getGameDetails();
      int gamemodeIndex = LaserTag::getGamemodeManager()->getCurrentGamemodeOption();
      jsonOut["gamemodeData"]["gamemodeIndex"] = gamemodeIndex;

      // convert JSON object to a string and send it back to the node requesting to join
      String msg = "";
      serializeJson(jsonOut, msg);
      mesh.sendSingle(from, msg);

    }


    void MeshManager::newConnectionCallback(uint32_t nodeId) {
#if DEBUG_SERIAL
      Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
#endif


    }

    void MeshManager::changedConnectionCallback() {
#if DEBUG_SERIAL
      Serial.printf("Changed connections\n");
#endif
    }

    void MeshManager::nodeTimeAdjustedCallback(int32_t offset) {
      // Do nothing with this information
    }

    void MeshManager::sendCommand(std::string commandCode) {
      // send a command over Wi-Fi
      JsonDocument jsonOut;
      jsonOut["control"] = ControlTypes::COMMAND;
      jsonOut["code"] = commandCode;
      Serial.println("sending the command" + String(commandCode.c_str()) + " over the mesh network");

      // convert JSON object to a string and send to all nodes on the network (apart from ourselves)
      String msg = "";
      serializeJson(jsonOut, msg);
      mesh.sendBroadcast(msg, false);
    }

    void MeshManager::sendUpdate() {
      // send a player state update over the network

      JsonDocument jsonOut;
      jsonOut["control"] = ControlTypes::UPDATE;

      // Put all the player's details into the JSON object
      PlayerWrapper *myPlayer = LaserTag::getPlayer();

      jsonOut["data"]["unitnum"] = myPlayer->getUnitnum();
      jsonOut["data"]["team"] = myPlayer->getTeam();
      jsonOut["data"]["name"] = myPlayer->getName();
      jsonOut["data"]["revives"] = myPlayer->getRevives();
      jsonOut["data"]["health"] = myPlayer->getHealth();
      jsonOut["data"]["kills"] = myPlayer->getKills();
      jsonOut["data"]["gunId"] = myPlayer->getGun()->getIndex();
      jsonOut["data"]["carryingFlag"] = myPlayer->getCarryingFlag();

      String msg = "";
      serializeJson(jsonOut, msg);
      mesh.sendBroadcast(msg, true); // send to all nodes on the network
      // send to ourselves, so we update our state for leaderboard too.
    }

    void MeshManager::handleUpdateRx(uint32_t from, String jsonData) {
      // This gets called when we rx an update over the network

      if (!LaserTag::getNetworkManager()->getInLobby()) // if not in a lobby ignore updates.
        return;

      JsonDocument jsonIn; // deserialize the json message
      deserializeJson(jsonIn, jsonData);

      Player updatedPlayer = { // convert the json data into a player object
              jsonIn["data"]["unitnum"],
              jsonIn["data"]["team"],
              jsonIn["data"]["name"],
              jsonIn["data"]["revives"],
              jsonIn["data"]["health"],
              jsonIn["data"]["kills"],
              jsonIn["data"]["carryingFlag"],
              jsonIn["data"]["gunId"]
      };

      // update the player in the network map
      LaserTag::getNetworkManager()->setPlayerInMap(from, updatedPlayer);
    }

    void MeshManager::sendHitConfirmation(int shooterUnitnum, int victimUnitnum, bool killConfirm) {
      // Send a signal over the network that a player has been hit/ killed.

      JsonDocument jsonOut;
      jsonOut["control"] = ControlTypes::HIT_CONFIRM;
      jsonOut["data"]["shooterUnitnum"] = shooterUnitnum;
      jsonOut["data"]["victimUnitnum"] = victimUnitnum;
      jsonOut["data"]["killConfirm"] = killConfirm;

      String msg = "";
      serializeJson(jsonOut, msg);

      if (killConfirm) { // if its a kill then send to all nodes on the network
        mesh.sendBroadcast(msg, false); // send to all nodes on the network

      } else { // if its just a hit then send to the shooter so we don't spam the network
        uint32_t shooterNodeID = LaserTag::getNetworkManager()->getPlayerIdByUnitnum(shooterUnitnum);
        mesh.sendSingle(shooterNodeID, msg);
      }

    }

} // Networks