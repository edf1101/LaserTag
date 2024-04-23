/*
 * Created by Ed Fillingham on 22/04/2024.
 *
 * This file manages, sends and receives messages on the mesh network.
*/

#include "MeshManager.h"

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

      if (millis() - lastMsg > 500) {
        lastMsg = millis();
        sendMessage();
      }
    }

    void MeshManager::sendMessage() {
      String msg = "Hello from node ";
      msg += String(millis()/1000);
      mesh.sendBroadcast(msg);

    }

// Needed for painless library
    void MeshManager::receivedCallback(uint32_t from, String &msg) {
      Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
    }

    void MeshManager::newConnectionCallback(uint32_t nodeId) {
      Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
    }

    void MeshManager::changedConnectionCallback() {
      Serial.printf("Changed connections\n");
    }

    void MeshManager::nodeTimeAdjustedCallback(int32_t offset) {
      Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
    }

} // Networks