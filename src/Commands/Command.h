/*
 * Created by Ed Fillingham on 23/06/2024.
 *
 * This class represents a command that can be sent over the system.
*/

#ifndef LASERTAG_COMMAND_H
#define LASERTAG_COMMAND_H

#include "CommandEnums.h"
#include <string>
#include <vector>

namespace Commands {

    class Command {
    public:
        // creator methods
        static void
        createCommand(std::string groupName, std::string commandName, int commandIndex); // creator for IR only commands
        static void createCommand(std::string groupName, std::string commandName,
                                  std::string commandCode); // creator for Wi-Fi only commands
        static void createCommand(std::string groupName, std::string commandName,
                                  std::string commandCode, int commandIndex); // creator for Wi-Fi or IR commands

        // Getters
        std::string getGroupName();

        std::string getCommandName();

        std::string getCommandCode();

        bool getIsWifiCommand(); // Gets whether this command is capable of being sent over Wi-Fi or not
        bool getIsIRCommand(); // Gets whether this command is capable of being sent over IR or not

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
        /* constructors are only used from inside the createCommand
         * functions in command class, so they can be private
         */
        Command(std::string groupName, std::string commandName, int commandIndex); // Constructor for IR only commands
        Command(std::string groupName, std::string commandName,
                std::string commandCode); // Constructor for Wi-Fi only commands
        Command(std::string groupName, std::string commandName,
                std::string commandCode, int commandIndex); // Constructor for Wi-Fi or IR commands

// The group and command names
        std::string groupName;
        std::string commandName;

        bool isWifiCommand = false; // Whether the command is capable of being sent over Wi-Fi
        bool isIRCommand = false; // Whether the command is capable of being sent over IR
// The command index (used for IR commands)
        int commandIndex = -1;
        std::string commandCode ="!!"; // The command code (used for Wi-Fi commands)

        inline static std::vector<Command *> systemCommands = {}; // A list of all the commands in the system.


    };

} // Commands

#endif //LASERTAG_COMMAND_H
