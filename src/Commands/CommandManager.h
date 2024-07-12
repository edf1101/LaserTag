/*
 * Created by Ed Fillingham on 12/05/2024.
 *
 * This class manages the flow of game commands in/out of the system.
*/

#ifndef LASERTAG_COMMANDMANAGER_H
#define LASERTAG_COMMANDMANAGER_H

#define GROUP_SIZE 20

#include "Command.h"
#include <string>

namespace Commands {

    enum commandSendType {
        BROADCAST,
        SINGLE,
        SELF
    };

    class CommandManager {
    public:
        void setupCommands(); // Set up the commands in the system
        void processCommand(Command *commandPointer); // Process the command
        void sendCommand(Command *commandPointer); // Send the command

        // getters and setters for the send type
        commandSendType getSendType();

        void setSendType(commandSendType newSendType);

        void setCmdTypeBroadcast(); // Setter for the command to send as a broadcast signal
        void setCmdTypeSingle(); // Setter for the command to send as a single signal
        void setCmdTypeSelf(); // Setter for the command to send as a broadcast signal

    private:
        // Whether to send the command to everyone (Wi-Fi), just the target (IR) or just ourself.
        commandSendType currentSendType = BROADCAST;
    };

} // Commands

#endif //LASERTAG_COMMANDMANAGER_H
