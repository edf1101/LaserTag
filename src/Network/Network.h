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

namespace Networks {

    class Network {
    public:
        void init(); // Initialises the network
        void loop(); // The main loop function for the network

        void disconnectNetwork();


        static void tryMakeAdmin(std::string adminCode); // Setter for the admin status
        static bool getAdminStatus() { return adminStatus; } // Getter for the admin status

        // pointer getters to important objects
        MessageQueue *getMessageQueue() { return &messageQueue; } // Getter for the message queue
    private:
        MessageQueue messageQueue; // The message queue

        MeshManager meshManager; // The mesh manager object

        inline static bool adminStatus = false;

    };

} // Networks

#endif //LASERTAG_NETWORK_H
