/*
 * Created by Ed Fillingham on 22/04/2024.
 *
 * This file manages, sends and receives messages on the mesh network.
*/

#ifndef LASERTAG_MESHMANAGER_H
#define LASERTAG_MESHMANAGER_H

#include "Arduino.h"
#include "../Libs/painlessMesh/src/painlessMesh.h"
#include "../config.h"
#include <vector>
#include <set>

using namespace std;

namespace Networks {

    enum ControlTypes { // Different types of control messages
        COMMAND,
        KILL_CONFIRM,
        UPDATE,
        JOIN,
        JOIN_ACKNOWLEDGE
    };

    enum JoinAckStates { // Different states for the join acknowledge message
        REJECT_INVALID_SUM,
        REJECT_BANNED,
        ACCEPT_NEW_GUN,
        ACCEPT_EXISTING_GUN
    };

    class MeshManager {
    public:
        void init();

        void loop();

        void disconnect();

        void sendJoinRequest();

        void sendCommand(std::string commandCode);

        void sendUpdate(); // send a player state update over the network

    private:
        Scheduler userScheduler; // to control your personal task
        painlessMesh mesh;
        long lastMsg;

        void nodeTimeAdjustedCallback(int32_t offset);

        void changedConnectionCallback();

        void newConnectionCallback(uint32_t nodeId);

        void receivedCallback(uint32_t from, String &msg);

        set<uint32_t> connectedNodes; // List of nodes that are connected
        set<uint32_t> activeNodes; // List of nodes that are active (recently sent a message)
        void handleLobbyJoinRequest(uint32_t from);

        void handleJoinLobbyAck(String jsonData); // Handle the join lobby acknowledge message

        void handleUpdateRx(uint32_t from, String jsonData); // Handle the update message
    };


} // Networks

#endif //LASERTAG_MESHMANAGER_H
