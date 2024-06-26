/*
 * Created by Ed Fillingham on 12/05/2024.
 *
 * This class manages the flow of game commands in/out of the system.
*/

#include "CommandManager.h"
#include "../LaserTag.h"

namespace Commands {

    void CommandManager::setupCommands() {
      // this function sets up all the commands in the system

      // Set up all the gamemodes
      Command::createCommand("Gamemodes", "None", "GA_NON");
      Command::createCommand("Gamemodes", "Solo", "GA_SOL");

      // Set up all the game modifications
      Command::createCommand("Test", "Test 1", "TS1");
      Command::createCommand("Test", "Test 2", "TS2");
      Command::createCommand("Test", "Test 3", "TS3");
      Command::createCommand("Test", "Test 4", "TS4");
      Command::createCommand("Test", "Test 5", "TS5");

      // Set up all the player commands

      // Set up all the team commands

      // Set up weapon types

      // set up weapon groups

    }

    void CommandManager::processCommand(Command *commandPointer) {
      // process an incoming command

      bool irCapable = commandPointer->getIsIRCommand();
      bool wifiCapable = commandPointer->getIsWifiCommand();
      string commandName = commandPointer->getCommandName();

      Serial.print("Processing command: ");
      Serial.println(commandName.c_str());
    }

    void CommandManager::sendCommand(Command *commandPointer) {
      // send an outgoing command

      bool irCapable = commandPointer->getIsIRCommand();
      bool wifiCapable = commandPointer->getIsWifiCommand();
      string commandName = commandPointer->getCommandName();

      Serial.print("sending command: ");
      Serial.println(commandName.c_str());
    }


} // Commands