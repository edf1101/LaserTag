/*
 * Created by Ed Fillingham on 22/04/2024.
 *
 * This file manages, sends and receives messages on the mesh network.
*/

#include "MeshManager.h"
#include "Network.h"

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

      } else if (control == ControlTypes::NAME_CHANGE) {
        // Do something on received name change

      } else if (control == ControlTypes::KILL_CONFIRM) {
        // Do something on received kill confirm

      } else if (control == ControlTypes::UPDATE) {
        // Do something on received update
        // If they aren't already in the game, add them to the game (this should only happen if admin has disconnected and reconnected)

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

      if ((JoinAckStates) jsonIn["joinState"] == JoinAckStates::REJECT_INVALID_SUM) {
        // If the join was rejected because of an invalid sum
        // TODO implement this

      } else if ((JoinAckStates) jsonIn["joinState"] == JoinAckStates::REJECT_BANNED) {
        // If the join was rejected because the node is banned
        // TODO implement this

      } else if ((JoinAckStates) jsonIn["joinState"] == JoinAckStates::ACCEPT_NEW_GUN) {
        // If the join was accepted and the node is a new gun
        Network::joinLobby(false);

      } else if ((JoinAckStates) jsonIn["joinState"] == JoinAckStates::ACCEPT_EXISTING_GUN) {
        // If the join was accepted and the node is an existing gun
        // TODO implement this
        Network::joinLobby(true, nullptr);

      }

    }

    void MeshManager::sendJoinRequest(){
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
        Serial.println("Node is already in the game");
        // If the node is already in the game find it's stats and send them back to make the node rejoin in last state.
        // This is useful if the node has been disconnected and reconnected and needs to rejoin the game
        // TODO implement this
        jsonOut["joinState"] = JoinAckStates::ACCEPT_EXISTING_GUN;

      } else {
        // If the node is not in the game add it to the game
        connectedNodes.insert(from);

        // pick a unitnum for the node
        // TODO implement this properly
        int unitnum = random(1, 127);
        Serial.println("Node is new Assigning it unitnum: " + String(unitnum));
        jsonOut["unitnum"] = unitnum;
        jsonOut["joinState"] = JoinAckStates::ACCEPT_NEW_GUN;
      }

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

} // Networks