/*
 * Created by Ed Fillingham on 23/06/2024.
 *
 * This class represents a command that can be sent over the system.
*/

#include "Command.h"

#include <utility>

namespace Commands {

    Command::Command(std::string groupName, std::string commandName, std::string commandCode, int commandIndex) {
      // constructor for the Command object when it's a Wi-Fi or IR command

      this->groupName = std::move(groupName);
      this->commandName = std::move(commandName);
      this->commandCode = std::move(commandCode);
      this->commandIndex = commandIndex;
      this->canBroadcast = true;
      this->canSingle = true;

    }

    void Command::createCommand(std::string groupName, std::string commandName,
                                std::string commandCode, int commandIndex) {
      // creates a Wi-Fi or IR command using the constructor on the Heap
      // so it's retained out of scope then adds it to the system commands list
      // This creator automatically assumes it can send Broadcast, single and self.

      auto *newCommand = new Command(std::move(groupName), std::move(commandName), std::move(commandCode),
                                     commandIndex);
      systemCommands.push_back(newCommand);
    }

    void Command::createCommand(std::string groupName, std::string commandName,
                                std::string commandCode, int commandIndex,
                                bool canBroadcast, bool canSingle, bool canSelf) {
      // creates a Wi-Fi or IR command using the constructor on the Heap
      // so it's retained out of scope then adds it to the system commands list
      // This creator allows you to specify if it can send Broadcast, single or self.

      // create it.
      auto *newCommand = new Command(std::move(groupName), std::move(commandName), std::move(commandCode),
                                     commandIndex);

      newCommand->modifySendType(canBroadcast, canSingle, canSelf); // modify its send type.

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

    std::string Command::getCommandCode() {
      // returns the command code of the command

      return commandCode;
    }

    bool Command::getCanBroadcast() {
      // returns whether the command is able to be sent over Wi-Fi or not.

      return canBroadcast;
    }

    bool Command::getCanSingle() {
      // returns whether the command is able to be sent over IR or not.

      return canSingle;
    }

    bool Command::getCanSelf() {
      // returns whether the command is able to be sent to just ourself.

      return canSingle;
    }

    int Command::getCommandIndex() {
      // return the command index

      return commandIndex;
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
            command->getCanBroadcast() == requiresWiFi && command->getCanSingle() == requiresIR) {
          commandsInGroup.push_back(command);
        }
      }

      return commandsInGroup;
    }

    bool Command::commandExists(std::string commandCode) {
      // returns whether a command exists in the system or not

      for (auto &command: systemCommands) {
        if (command->getCanBroadcast() && command->commandCode == commandCode) {
          return true;
        }
      }

      return false;
    }

    bool Command::commandExists(int commandId) {
      // returns whether a command exists in the system or not

      for (auto &command: systemCommands) {
        if (command->getCanSingle() && command->commandIndex == commandId) {
          return true;
        }
      }

      return false;
    }

    Command *Command::getCommandByCode(std::string commandCode) {
      // return a pointer to a command object by its command code. If the command doesn't exist, return nullptr

      for (auto &command: systemCommands) {
        if (command->commandCode == commandCode) {
          return command;
        }
      }
      return nullptr;
    }

    Command *Command::getCommandByIndex(int commandIndex) {
      // return a pointer to a command object by its command index. If the command doesn't exist, return nullptr

      for (auto &command: systemCommands) {
        if (command->commandIndex == commandIndex) {
          return command;
        }
      }
      return nullptr;
    }

    void Command::modifySendType(bool canBroadcast, bool canSingle, bool canSelf) {
      // modify who the command can send to

      this->canBroadcast = canBroadcast;
      this->canSingle = canSingle;
      this->canSelf = canSelf;
    }

}
// Commands