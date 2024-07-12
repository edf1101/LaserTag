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

      // The (x* groupSize) + y commandIndex is so that when sending a command the index is made up of
      // groups then the command inside that group for ease of reading / modification.

      // Set up all the gamemodes
      Command::createCommand("Gamemodes", "None", "GA_NON", (0 * GROUP_SIZE) + 0,
                             true, false, false);
      Command::createCommand("Gamemodes", "Solo", "GA_SOL", (0 * GROUP_SIZE) + 1,
                             true, false, false);

      // Set up all the game modifications
      Command::createCommand("Game Mods", "Play", "GM_PLA", (1 * GROUP_SIZE) + 0,
                             true, false, false);
      Command::createCommand("Game Mods", "Pause", "GM_PAU", (1 * GROUP_SIZE) + 1,
                             true, false, false);

      // Set up all the player commands
      Command::createCommand("Players", "+1 Life", "PL_1L", (2 * GROUP_SIZE) + 0);
      Command::createCommand("Players", "-1 Life", "PL_REMLIFE", (2 * GROUP_SIZE) + 1);
      Command::createCommand("Players", "0 Lives", "PL_0L", (2 * GROUP_SIZE) + 2);
      Command::createCommand("Players", "Infinite Mags", "PL_INFMAGS", (2 * GROUP_SIZE) + 3);
      Command::createCommand("Players", "Infinite Ammo", "PL_INFAMMO", (2 * GROUP_SIZE) + 4);
      Command::createCommand("Players", "Normal Ammo", "PL_NORMAMMO", (2 * GROUP_SIZE) + 5);
      Command::createCommand("Players", "Infinite Lives", "PL_INFLIVES", (2 * GROUP_SIZE) + 6);
      Command::createCommand("Players", "Invincible", "PL_INVIN", (2 * GROUP_SIZE) + 7);
      Command::createCommand("Players", "Normal Lives", "PL_NORMLIVES", (2 * GROUP_SIZE) + 8);
      Command::createCommand("Players", "Suppressor", "PL_SUP", (2 * GROUP_SIZE) + 9);
      Command::createCommand("Players", "Suppressor Off", "PL_SUP_OFF", (2 * GROUP_SIZE) + 10);
      Command::createCommand("Players", "High Fire Rate", "PL_FIRE_HI", (2 * GROUP_SIZE) + 11);
      Command::createCommand("Players", "Slow Fire Rate", "PL_FIRE_LO", (2 * GROUP_SIZE) + 12);
      Command::createCommand("Players", "Normal Fire Rate", "PL_FIRE_NOR", (2 * GROUP_SIZE) + 13);
      Command::createCommand("Players", "Fake Kill Confirm", "PL_KIL_CONF", (2 * GROUP_SIZE) + 14);

      // Set up all the team commands

      // Set up weapon types
      Command::createCommand("Guns", "Guns Swappable", "GUN_SWAP", (3 * GROUP_SIZE) + 0);
      Command::createCommand("Guns", "Guns Unswappable", "GUN_SWAP_OFF", (3 * GROUP_SIZE) + 1);

      // now add all of the guns
      vector<Weapons::Gun> allGuns = WeaponsManager::getAllGuns();
      int i = 2; // start on 2 as we have already added the swappable and unswappable commands
      for (auto &gun: allGuns) {
        Command::createCommand("Guns", gun.getName(),
                               "GUN_" + gun.getAcronym(), (3 * GROUP_SIZE) + i);
        i++;
      }


      // set up weapon groups
      vector<Weapons::GunGroup *> allGunGroups = WeaponsManager::getGunGroups();
      i = 0;
      for (auto &gunGroup: allGunGroups) {
        Command::createCommand("Gun Groups", gunGroup->getName() + " On",
                               "GG_" + gunGroup->getName() + "_ON", (3 * GROUP_SIZE) + (i * 2));
        Command::createCommand("Gun Groups", gunGroup->getName() + " Off",
                               "GG_" + gunGroup->getName() + "_OFF", (3 * GROUP_SIZE) + (i * 2) + 1);
        i++;
      }

    }

    void CommandManager::processCommand(Command *commandPointer) {
      // process an incoming command

      string commandGroup = commandPointer->getGroupName();
      string commandName = commandPointer->getCommandName();

      Serial.print("Processing command: ");
      Serial.println(commandName.c_str());

      Networks::MessageQueue *messageQueue = LaserTag::getNetworkManager()->getMessageQueue();
      PlayerWrapper *myPlayer = LaserTag::getPlayer();

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

        }
      } else if (commandGroup == "Players") {

        if (commandName == "+1 Life") {
          // add a life to the player

          Serial.println("Adding a life to the player");
          if (myPlayer->getRevives() < MAX_REVIVES) {
            myPlayer->setRevives(myPlayer->getRevives() + 1);
          }
        } else if (commandName == "-1 Life") {
          // remove a life from the player

          if (myPlayer->getRevives() > 0) {
            myPlayer->setRevives(myPlayer->getRevives() - 1);
          }
          Serial.println("Removing a life from the player");
//          LaserTag::getPlayer()->removeLife();
        } else if (commandName == "0 Lives") {
          // set the player to 0 lives

          Serial.println("Setting player to 0 lives");
          myPlayer->setRevives(0);
        } else if (commandName == "Infinite Mags") {
          // set the player to infinite mags

          myPlayer->getGun()->setInfiniteAmmoState(Weapons::INFINITE_MAGS);
          Serial.println("Setting player to infinite mags");
        } else if (commandName == "Infinite Ammo") {
          // set the player to have infinite ammo

          myPlayer->getGun()->setInfiniteAmmoState(Weapons::INFINITE_AMMO);
          Serial.println("Setting player to have infinite ammo");
        } else if (commandName == "Normal Ammo") {
          // set the player to not have infinite ammo

          myPlayer->getGun()->setInfiniteAmmoState(Weapons::NORMAL_AMMO);
          Serial.println("Setting player to have normal ammo");
        } else if (commandName == "Infinite Lives") {
          // Set the player to have infinite Lives

          myPlayer->setInfiniteLivesState(PlayerWrapper::INFINITE_LIVES);
          Serial.println("Setting player to have infinite lives");
        } else if (commandName == "Invincible") {
          // Set the player to be invincible

          myPlayer->setInfiniteLivesState(PlayerWrapper::INVINCIBLE_LIVES);
          Serial.println("Setting player to be invincible");
        } else if (commandName == "Normal Lives") {
          // Set the player to not be invincible or infinite lives

          myPlayer->setInfiniteLivesState(PlayerWrapper::NORMAL_LIVES);
          Serial.println("Setting player to not be invincible");
        } else if (commandName == "Suppressor") {
          // Set the player to have a suppressor

          Serial.println("Setting player to have a suppressor");
          myPlayer->getGun()->setSuppressed(true);
        } else if (commandName == "Suppressor Off") {
          // Set the player to not have a suppressor

          Serial.println("Setting player to not have a suppressor");
          myPlayer->getGun()->setSuppressed(false);
        } else if (commandName == "High Fire Rate") {
          // Set the player to have a high fire rate

          myPlayer->getGun()->setFireRate(Weapons::FireRate::FAST);
          Serial.println("Setting player to have a high fire rate");
        } else if (commandName == "Slow Fire Rate") {
          // Set the player to have a slow fire rate

          myPlayer->getGun()->setFireRate(Weapons::FireRate::SLOW);
          Serial.println("Setting player to have a slow fire rate");
        } else if (commandName == "Normal Fire Rate") {
          // Set the player to have a normal fire rate

          myPlayer->getGun()->setFireRate(Weapons::FireRate::NORMAL);
          Serial.println("Setting player to have a normal fire rate");
        } else if (commandName == "Fake Kill Confirm") {
          // Set the player to have a fake kill confirm

          myPlayer->setKills(myPlayer->getKills() + 1);
          Serial.println("Setting player to have a fake kill confirm");
        }

      } else if (commandGroup == "Guns") {
        if (commandName == "Guns Swappable") {
          // Set the guns to be swappable

          WeaponsManager::setGunsSwappable(true);
          Serial.println("Setting guns to be swappable");
        } else if (commandName == "Guns Unswappable") {
          // Set the guns to not be swappable

          WeaponsManager::setGunsSwappable(false);
          Serial.println("Setting guns to not be swappable");
        } else {
          // Set the player's gun to the selected gun

          Weapons::Gun newGun = WeaponsManager::getGun(commandName);
          myPlayer->swapGun(newGun.getName());
          Serial.print("Setting player to have the gun: ");
          Serial.println(newGun.getName().c_str());
        }
      } else if (commandGroup == "Gun Groups") {
        // Set the gun group to be on or off

        std::string groupName = commandName.substr(0, commandName.find(" ", 0));
        std::string state = commandName.substr(commandName.find(' ', 0) + 1);
        bool stateBool = state == "On";
        WeaponsManager::setGroupUseState(groupName, stateBool);
        Serial.print("Setting gun group ");
        Serial.print(groupName.c_str());
        Serial.print(" to ");
        Serial.println(state.c_str());

        // Now check if we need to change the player's gun
        Weapons::Gun *currentGun = myPlayer->getGun();
        std::vector<Weapons::Gun> allGuns = WeaponsManager::getAllGuns();
        bool currentGunFound = false;
        bool defaultGunFound = false;
        for (auto &gun: allGuns) {
          if (gun.getName() == currentGun->getName()) {
            currentGunFound = true;
          }
          if (gun.getName() == WeaponsManager::defaultGun) {
            defaultGunFound = true;
          }
        }

        if (currentGunFound) return; // if the current gun is still in the active guns then return

        // we need to swap the gun.
        if (defaultGunFound) // if the default gun is still in the active guns then swap to that
          myPlayer->swapGun(WeaponsManager::defaultGun);
        else {
          // if the default gun isn't in the active guns then swap to the first gun in the list
          myPlayer->swapGun(allGuns[0].getName());
        }

      }
    }

    void CommandManager::sendCommand(Command *commandPointer) {
      // send an outgoing command

      string commandName = commandPointer->getCommandName();

      Serial.print("sending command: ");
      Serial.println(commandName.c_str());
      if (currentSendType == BROADCAST and commandPointer->getCanBroadcast()) {
        LaserTag::getNetworkManager()->sendCommand(commandPointer->getCommandCode());
        processCommand(commandPointer); // as it's a broadcast, process the command locally too
      } else if (currentSendType == SELF and commandPointer->getCanSelf()) {
        // as it's a self sending command, process the command locally only
        processCommand(commandPointer);
      } else if (currentSendType == SINGLE and commandPointer->getCanSingle()) {
        LaserTag::getFiring()->sendCommand(commandPointer->getCommandIndex());
      }

      if ((!commandPointer->getCanBroadcast() && currentSendType == BROADCAST) ||
          (!commandPointer->getCanSelf() && currentSendType == SELF) ||
          (!commandPointer->getCanSingle() && currentSendType == SINGLE)) {
        Serial.println("Trying to send a command that isn't able to be sent with this type");
      }
    }

    commandSendType CommandManager::getSendType() {
      // getter for the broadcast state

      return currentSendType;
    }

    void CommandManager::setSendType(commandSendType newSendType) {
      // setter for the broadcast state

      this->currentSendType = newSendType;
    }

    void CommandManager::setCmdTypeBroadcast() {
      // setter for the command to send as a broadcast signal

      this->currentSendType = BROADCAST;
    }

    void CommandManager::setCmdTypeSingle() {
      // setter for the command to send as a single signal

      this->currentSendType = SINGLE;
    }

    void CommandManager::setCmdTypeSelf() {
      // setter for the command to send as a broadcast signal

      this->currentSendType = SELF;
    }

} // Commands