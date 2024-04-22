/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This class handles the network functionality of the gun.
*/

#ifndef LASERTAG_NETWORK_H
#define LASERTAG_NETWORK_H

#include "MessageQueue.h"

namespace Networks {

    class Network {
    public:
        void init(); // Initialises the network

        // pointer getters to important objects
        MessageQueue *getMessageQueue() { return &messageQueue; } // Getter for the message queue
    private:
        MessageQueue messageQueue; // The message queue
    };

} // Networks

#endif //LASERTAG_NETWORK_H
