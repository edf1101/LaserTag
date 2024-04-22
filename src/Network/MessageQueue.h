/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This represents the message queue that stores messages sent between the guns.
*/

#ifndef LASERTAG_MESSAGEQUEUE_H
#define LASERTAG_MESSAGEQUEUE_H

#include <vector>
#include <string>
#include "Arduino.h"

namespace Networks {

    class MessageQueue {
    public:
        void pushMessage(std::string message); // function to add a message to the queue

        std::vector<std::string> *getMessages() { return messages; } // function to get the messages
        std::vector<unsigned long> *getMessageTimes() { return messageTimes; } // function to get the message times

        void clear(); // function to clear the messages

    private:
        std::vector<std::string> *messages = new std::vector<std::string>; // vector to store messages
        std::vector<unsigned long> *messageTimes= new std::vector<unsigned long>; // vector to store messages

    };

} // Networks

#endif //LASERTAG_MESSAGEQUEUE_H
