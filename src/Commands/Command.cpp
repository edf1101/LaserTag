/*
 * Created by Ed Fillingham on 23/06/2024.
 *
 * This class represents a command that can be sent over the system.
*/

#include "Command.h"

#include <utility>

namespace Commands {
    Command::Command(std::string groupName, std::string commandName, int commandIndex) {
      // constructor for the Command object when it's an IR only command

      this->groupName = std::move(groupName);
      this->commandName = std::move(commandName);
      this->commandIndex = commandIndex;
      this->isWifiCommand = false;
      this->isIRCommand = true;

//      systemCommands.push_back(*this); // add the command to the list of all commands in the system
    }

    Command::Command(std::string groupName, std::string commandName, std::string commandCode) {
      // constructor for the Command object when it's a Wi-Fi only command

      this->groupName = std::move(groupName);
      this->commandName = std::move(commandName);
      this->commandCode = std::move(commandCode);
      this->isWifiCommand = true;
      this->isIRCommand = false;

    }

    Command::Command(std::string groupName, std::string commandName, std::string commandCode, int commandIndex) {
      // constructor for the Command object when it's a Wi-Fi or IR command

      this->groupName = std::move(groupName);
      this->commandName = std::move(commandName);
      this->commandCode = std::move(commandCode);
      this->commandIndex = commandIndex;
      this->isWifiCommand = true;
      this->isIRCommand = true;

    }

    void Command::createCommand(std::string groupName, std::string commandName, int commandIndex) {
      // creates an IR only command using the constructor on the Heap
      // so it's retained out of scope then adds it to the system commands list

      auto *newCommand = new Command(std::move(groupName), std::move(commandName), commandIndex);
      systemCommands.push_back(newCommand);
    }

    void Command::createCommand(std::string groupName, std::string commandName, std::string commandCode) {
      // creates a Wi-Fi only command using the constructor on the Heap
      // so it's retained out of scope then adds it to the system commands list

      auto *newCommand = new Command(std::move(groupName), std::move(commandName), std::move(commandCode));
      systemCommands.push_back(newCommand);
    }

    void
    Command::createCommand(std::string groupName, std::string commandName, std::string commandCode, int commandIndex) {
      // creates a Wi-Fi or IR command using the constructor on the Heap
      // so it's retained out of scope then adds it to the system commands list

      auto *newCommand = new Command(std::move(groupName), std::move(commandName), std::move(commandCode),
                                     commandIndex);
      systemCommands.push_back(newCommand);
    }

    std::string Command::getGroupName() {
      // returns the group name of the command

      return groupName;
    }

    std::string Command::getCommandName() {
      // returns the command name of the command

      return commandName;
    }

    bool Command::getIsWifiCommand() {
      // returns whether the command is able to be sent over Wi-Fi or not.

      return isWifiCommand;
    }

    bool Command::getIsIRCommand() {
      // returns whether the command is able to be sent over IR or not.

      return isIRCommand;
    }

    std::vector<Command *> Command::getCommandsByGroup(std::string groupName) {
      // returns all the commands in a group. If the group doesn't exist, return an empty vector

      std::vector<Command *> commandsInGroup;

      for (auto &command: systemCommands) {
        if (command->getGroupName() == groupName) {
          commandsInGroup.push_back(command);
        }
      }

      return commandsInGroup;
    }

    /*
     * BELOW ARE THE FUNCTIONS FOR THE STATIC SIDE OF THE COMMAND CLASS.
     */

    std::vector<Command *> Command::getCommandsByGroup(std::string groupName, bool requiresWiFi, bool requiresIR) {
      // returns all the commands in a group. If the group doesn't exist, return an empty vector
      // If requireWiFi is true, only return Wi-Fi commands. If it's false, only return IR commands

      std::vector<Command *> commandsInGroup;

      for (auto &command: systemCommands) {
        if (command->getGroupName() == groupName &&
            command->getIsWifiCommand() == requiresWiFi && command->getIsIRCommand() == requiresIR) {
          commandsInGroup.push_back(command);
        }
      }

      return commandsInGroup;
    }

    bool Command::commandExists(std::string commandCode) {
      // returns whether a command exists in the system or not

      for (auto &command: systemCommands) {
        if (command->getIsWifiCommand() && command->commandCode == commandCode) {
          return true;
        }
      }

      return false;
    }

    bool Command::commandExists(int commandId) {
      // returns whether a command exists in the system or not

      for (auto &command: systemCommands) {
        if (command->getIsIRCommand() && command->commandIndex == commandId) {
          return true;
        }
      }

      return false;
    }

    Command *Command::getCommandByCode(std::string commandCode) {
      // return a pointer to a command object by its command code. If the command doesn't exist, return nullptr

      for (auto &command: systemCommands) {
        if (command->getIsIRCommand() && command->commandCode == commandCode) {
          return command;
        }
      }
      return nullptr;
    }

    Command *Command::getCommandByIndex(int commandIndex) {
      // return a pointer to a command object by its command index. If the command doesn't exist, return nullptr

      for (auto &command: systemCommands) {
        if (command->getIsWifiCommand() && command->commandIndex == commandIndex) {
          return command;
        }
      }
      return nullptr;
    }

}
// Commands