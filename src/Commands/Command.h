/*
 * Created by Ed Fillingham on 23/06/2024.
 *
 * This class represents a command that can be sent over the system.
*/

#ifndef LASERTAG_COMMAND_H
#define LASERTAG_COMMAND_H

#include <string>
#include <vector>

namespace Commands {

    class Command {
    public:
        // creator methods
        static void createCommand(std::string groupName, std::string commandName,
                                  std::string commandCode, int commandIndex); // creator for Wi-Fi or IR commands

        static void createCommand(std::string groupName, std::string commandName,
                                  std::string commandCode, int commandIndex,
                                  bool canBroadcast, bool canSingle, bool canSelf);

        // Getters
        std::string getGroupName();

        std::string getCommandName();

        std::string getCommandCode();

        int getCommandIndex();

        bool getCanBroadcast(); // Gets whether this command is capable of being sent over Wi-Fi or not
        bool getCanSingle(); // Gets whether this command is capable of being sent over IR or not
        bool getCanSelf(); // Get whether we can send this command to ourself.

        // static functions to interact with the system commands
        static std::vector<Command *> getCommandsByGroup(std::string groupName); // Get all commands in a group
        // Get all commands in a group as long as its Wi-Fi/IR status matches the requireWiFi/IR parameter
        static std::vector<Command *> getCommandsByGroup(std::string groupName,
                                                         bool requiresWiFi, bool requiresIR);

        static bool commandExists(std::string commandCode); // Check if a command exists
        static bool commandExists(int commandId); // Check if a command exists

        static Command *getCommandByCode(std::string commandCode); // Get a command by its command code
        static Command *getCommandByIndex(int commandIndex); // Get a command by its index


    private:
        /* constructor is only used from inside the createCommand
         * functions in command class, so it can be private
         */
        Command(std::string groupName, std::string commandName,
                std::string commandCode, int commandIndex); // Constructor for Wi-Fi or IR commands, sends to all.

        void modifySendType(bool canBroadcast, bool canSingle, bool canSelf); // modify who the command can send to

// The group and command names
        std::string groupName;
        std::string commandName;

        bool canBroadcast = false; // Whether the command is capable of being sent to everyone over Wi-Fi
        bool canSingle = false; // Whether the command is capable of being sent to individuals over IR
        bool canSelf = false; // Whether the command is capable of being sent to just myself
// The command index (used for IR commands)
        int commandIndex = -1;
        std::string commandCode = "!!"; // The command code (used for Wi-Fi commands)

        inline static std::vector<Command *> systemCommands = {}; // A list of all the commands in the system.


    };

} // Commands

#endif //LASERTAG_COMMAND_H
