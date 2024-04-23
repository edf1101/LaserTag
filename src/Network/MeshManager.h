/*
 * Created by Ed Fillingham on 22/04/2024.
 *
 * This file manages, sends and receives messages on the mesh network.
*/

#ifndef LASERTAG_MESHMANAGER_H
#define LASERTAG_MESHMANAGER_H

#include "Arduino.h"
#include "../libs/painlessMesh/src/painlessMesh.h"
#include "../config.h"

namespace Networks {

    class MeshManager {
    public:
        void init();

        void loop();

        void disconnect();


    private:
        Scheduler userScheduler; // to control your personal task
        painlessMesh  mesh;
        long lastMsg;

        void nodeTimeAdjustedCallback(int32_t offset);

        void changedConnectionCallback();

        void newConnectionCallback(uint32_t nodeId);

        void receivedCallback(uint32_t from, String &msg);

        void sendMessage();

    };


} // Networks

#endif //LASERTAG_MESHMANAGER_H
