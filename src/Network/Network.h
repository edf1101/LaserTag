/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This class handles the network functionality of the gun.
*/

#ifndef LASERTAG_NETWORK_H
#define LASERTAG_NETWORK_H

#include "MessageQueue.h"
#include "../config.h"
#include <string>
#include "MeshManager.h"
#include "../Players/Player.h"

namespace Networks {

    class Network {
    public:
        void init(); // Initialises the network
        void loop(); // The main loop function for the network

        void disconnectNetwork();


        static void tryMakeAdmin(std::string adminCode); // Setter for the admin status
        static bool getAdminStatus() { return adminStatus; } // Getter for the admin status

        static void joinLobby(bool alreadyInGame, Player *myPlayer = nullptr); // Join the lobby
        static bool getInLobby() { return inLobby; } // Getter for the inLobby status

        // pointer getters to important objects
        MessageQueue *getMessageQueue() { return &messageQueue; } // Getter for the message queue
        MessageQueue *getDebugMessageQueue() { return &debugMessageQueue; } // Getter for the message queue
    private:
        MessageQueue messageQueue; // The message queue
        MessageQueue debugMessageQueue; // The message queue

        MeshManager meshManager; // The mesh manager object

        inline static bool adminStatus = false;
        inline static bool inLobby = false; // If the gun is in the lobby

        unsigned long lastJoinRequestSent = 0; // The last time a join request was sent

    };

} // Networks

#endif //LASERTAG_NETWORK_H
