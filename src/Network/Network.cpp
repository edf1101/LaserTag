/*
 * Created by Ed Fillingham on 20/04/2024.
*/

#include "Network.h"

namespace Networks {


    void Network::init() {

      // Set up the message Queue
      for(int i = 0; i<16;i++){
        messageQueue.pushMessage("");
      }

     }
} // Networks