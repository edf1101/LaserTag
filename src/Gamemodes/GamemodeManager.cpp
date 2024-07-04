/*
 * Created by Ed Fillingham on 14/04/2024.
 *
 * This class abstracts the complexity of managing / switching gamemodes.
*/

#include "GamemodeManager.h"
#include "../LaserTag.h"

void GamemodeManager::init(LaserTag *system) {
  // Set the initial gamemode to none
  mySystem = system; // assign the pointer to the main system object
  currentGamemode = new GamemodeNone(mySystem);
}

Gamemode *GamemodeManager::getCurrentGame() {
  // Get the current gamemode

  return currentGamemode;
}

void GamemodeManager::switchGamemode(GamemodeManager::GamemodeOptions _option) {
  // clean up the current gamemode
  delete currentGamemode;

  // Switch the gamemode to the specified option
  switch (_option) {
    case NONE:
      currentGamemode = new GamemodeNone(mySystem);
      break;
    case SOLO:
      currentGamemode = new GamemodeSolo(mySystem);
      break;
  }
  currentGamemodeOption = _option; // update the current gamemode option

  // make sure players are reset to the new gamemode's template player
  // first update our own player
  LaserTag::getPlayer()->setPlayerToTemplate(currentGamemode->getPlayerTemplate());

  // update all players in our network status hashmap to the new gamemode's template player
  std::vector<uint32_t> nodeIDs = LaserTag::getNetworkManager()->getAllPlayerNodeIDs();
  for (uint32_t nodeID: nodeIDs) {

    Player *playerRef = LaserTag::getNetworkManager()->getPlayerInMap(nodeID);
    PlayerWrapper::setPlayerToTemplate(playerRef,
                                       currentGamemode->getPlayerTemplate());
  }

  // add a message to the message queue saying we joined a game.
  std::string gameName = currentGamemode->getName();
  LaserTag::getNetworkManager()->getMessageQueue()->pushMessage("Joined " + gameName + " game");
}

void GamemodeManager::switchGamemodeByInt(int _option) {
  // Switch the gamemode to the specified option (the integer refers to the enum index)

  Serial.println("Switching to" + String(_option) + " gamemode.");
  switchGamemode((GamemodeOptions) _option);
}




