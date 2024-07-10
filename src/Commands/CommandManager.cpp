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
      Command::createCommand("Game Mods", "Play", "GM_PLA");
      Command::createCommand("Game Mods", "Pause", "GM_PAU");

      // Set up all the player commands

      // Set up all the team commands

      // Set up weapon types

      // set up weapon groups

    }

    void CommandManager::processCommand(Command *commandPointer) {
      // process an incoming command

      string commandGroup = commandPointer->getGroupName();
      string commandName = commandPointer->getCommandName();

      Serial.print("Processing command: ");
      Serial.println(commandName.c_str());

      Networks::MessageQueue* messageQueue = LaserTag::getNetworkManager()->getMessageQueue();

      if (commandGroup == "Gamemodes") { // process the gamemode commands

        if (commandName == "None") {
          // set the gamemode to none
          LaserTag::getGamemodeManager()->switchGamemode(GamemodeManager::GamemodeOptions::NONE);
          Serial.println("Switching gamemode to none");
        } else if (commandName == "Solo") {
          // set the gamemode to solo
          LaserTag::getGamemodeManager()->switchGamemode(GamemodeManager::GamemodeOptions::SOLO);
          Serial.println("Switching gamemode to solo");
        }
      } else if (commandGroup == "Game Mods") { // Process the game modification commands
        if (commandName == "Play") {
          // set the game to play
          Serial.println("Setting game to play");
          LaserTag::getGamemodeManager()->getCurrentGame()->setGamePauseState(false);
          messageQueue->pushMessage("Game started!");

        } else if (commandName == "Pause") {
          // set the game to pause
          Serial.println("Setting game to paused");
          LaserTag::getGamemodeManager()->getCurrentGame()->setGamePauseState(true);
          messageQueue->pushMessage("Game paused!");

        } else if (commandName == "End Game") {
          // end the game
          Serial.println("Ending game");
//        TODO  LaserTag::getGamemodeManager()->getCurrentGame()->endGame();
        }
      }

    }

    void CommandManager::sendCommand(Command *commandPointer) {
      // send an outgoing command

      bool irCapable = commandPointer->getIsIRCommand();
      bool wifiCapable = commandPointer->getIsWifiCommand();
      string commandName = commandPointer->getCommandName();

      Serial.print("sending command: ");
      Serial.println(commandName.c_str());
      if (broadcast) {
        LaserTag::getNetworkManager()->sendCommand(commandPointer->getCommandCode());
        processCommand(commandPointer); // as it's a broadcast, process the command locally
      }
    }

    bool CommandManager::getBroadcast() {
      // getter for the broadcast state

      return broadcast;
    }

    void CommandManager::setBroadcast(bool _broadcast) {
      // setter for the broadcast state

      this->broadcast = _broadcast;
    }


} // Commands