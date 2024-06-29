/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This class handles the network functionality of the gun.
*/

#ifndef LASERTAG_NETWORK_H
#define LASERTAG_NETWORK_H

#include "MessageQueue.h"
#include "ArduinoJson.h"
#include "../config.h"
#include <string>
#include "MeshManager.h"
#include "../Players/Player.h"
#include <unordered_map>

namespace Networks {

    class Network {
    public:
        void init(); // Initialises the network
        void loop(); // The main loop function for the network

        void disconnectNetwork();

 // TODO these should probs be destatic-ed as u can access them statically thru laser tag class
        static void tryMakeAdmin(std::string adminCode); // Setter for the admin status
        static bool getAdminStatus() { return adminStatus; } // Getter for the admin status

        static void joinLobby( Player myPlayerTemplate); // Join the lobby
        static bool getInLobby() { return inLobby; } // Getter for the inLobby status

        // pointer getters to important objects
        MessageQueue *getMessageQueue() { return &messageQueue; } // Getter for the message queue
        MessageQueue *getDebugMessageQueue() { return &debugMessageQueue; } // Getter for the message queue

        // functions (getters & setters) for the players map
        static void setPlayerInMap(uint32_t id, Player player); // Add a player to the map
        static Player* getPlayerInMap(uint32_t id); // Get a player from the map
        static vector<uint32_t> getAllPlayerNodeIDs(); // returns all players in the map (the keys)

        void sendCommand(std::string commandCode); // Send a command

        void loadGamemodeDetails(JsonObject gameData); // load into a gamemode according to network data details

    private:
        MessageQueue messageQueue; // The message queue
        MessageQueue debugMessageQueue; // The message queue

        MeshManager meshManager; // The mesh manager object

        inline static bool adminStatus = false;
        inline static bool inLobby = false; // If the gun is in the lobby

        unsigned long lastJoinRequestSent = 0; // The last time a join request was sent

        // The players map is a map of the player id to the player object.
        // The idea is that you can add a player to the map, and then get a pointer to the player and modify it.
        inline static std::unordered_map<uint32_t, Player> playersMap;

        unsigned long lastStatusUpdateSent = 0; // The last time a status update was sent

    };

} // Networks

#endif //LASERTAG_NETWORK_H
