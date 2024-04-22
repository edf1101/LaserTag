/*
 * Created by Ed Fillingham on 20/04/2024.
 *
 * This represents the message queue that stores messages sent between the guns.
*/

#include "MessageQueue.h"

namespace Networks {

    void MessageQueue::pushMessage(std::string message) {
      // adds a message to the queue

      messages->insert(messages->begin(), message); // Add the message to the front of the vector
      if (messages->size() > 16)
        messages->erase(messages->end()); // Remove the last message in the vector

      messageTimes->insert(messageTimes->begin(), millis()); // Add the message time to the front of the vector
      if (messages->size() > 16)
        messageTimes->erase(messageTimes->end()); // Remove the last message time in the vector
    }

    void MessageQueue::clear() {
      // clears the messages
      messages->clear();
      messageTimes->clear();
    }
} // Networks