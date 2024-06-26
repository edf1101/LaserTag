/*
 * Created by Ed Fillingham on 12/05/2024.
 *
 * This class manages the flow of game commands in/out of the system.
*/

#ifndef LASERTAG_COMMANDMANAGER_H
#define LASERTAG_COMMANDMANAGER_H

#include "CommandEnums.h"
#include "Command.h"
#include <string>

namespace Commands {

    class CommandManager {
    public:
        void setupCommands(); // Set up the commands in the system
        void processCommand(Command *commandPointer); // Process the command
        void sendCommand(Command *commandPointer); // Send the command

        // getters and setters for the broadcast state
        bool getBroadcast();
        void setBroadcast(bool broadcast);

    private:
        bool broadcast = true; // Whether to send the command to everyone (wifi) or just the target (IR)
    };

} // Commands

#endif //LASERTAG_COMMANDMANAGER_H
