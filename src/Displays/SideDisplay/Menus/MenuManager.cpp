/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This class manages all the menus in the system.
*/


#include "MenuManager.h"
#include "../SideDisplay.h"
#include <functional>
#include "../../../LaserTag.h"
#include "../../../Network/Network.h"
#include "../../../Commands/CommandManager.h"

MenuManager::MenuManager(SideDisplay *_sideDisplay) {
  sideDisplay = _sideDisplay; // assign the pointer to the side display

  currentMenu = &mainMenu; // create a new menu
}

Menu *MenuManager::getCurrentMenu() {
  // get the current menu
  return currentMenu;
}

void MenuManager::onRotaryTurned(int change) {
  // called when the rotary encoder is turned
  currentMenu->onRotaryTurned(change);
}

void MenuManager::onRotaryPressed() {
  // called when the button is pressed
  currentMenu->onRotaryPressed();
}

void MenuManager::switchMenu(Menu *newMenu) {
  // This function switches the current menu to a new menu

  // check if new menu requires admin
  if (newMenu->getRequiresAdmin() && !Networks::Network::getAdminStatus()) {
    // if it does and the player is not an admin, return
    return;
  }


  // erase old menu
  currentMenu->erase();
  // set new menu
  currentMenu = newMenu;
  currentMenu->resetMenu();
  currentMenu->display(true);

}

void MenuManager::display(bool force) {
  currentMenu->display(force); // display the menu
}

void MenuManager::init() {
  // create the menu objects

  mainMenu.init(sideDisplay);
  mainMenu.addSubMenu("Scores", Images::img_menuLeaderboard, &leaderboardMenu);
  mainMenu.addSubMenu("Msgs", Images::img_menuMessages, &messageMenu);
  mainMenu.addSubMenu("Guns", Images::img_menuGuns, &gunMenu);
  mainMenu.addSubMenu("Settings", Images::img_menuSettings, &settingsMenu);
  mainMenu.addSubMenu("Admin", Images::img_menuAdmin, &adminMenu);

  leaderboardMenu.init(sideDisplay, &mainMenu);

  settingsMenu.init(sideDisplay);
  settingsMenu.setParentMenu(&mainMenu);
  settingsMenu.addSubMenu("Name", Images::img_menuName, &nameMenu);
  settingsMenu.addFunction("Turn Off", Images::img_menuTurnOff, std::bind(&LaserTag::turnOff));
  settingsMenu.addSubMenu("Admin #", Images::img_menuAdmin, &adminPasswordMenu);
  settingsMenu.addSubMenu("Debug", Images::img_menuMessages, &debugMsgMenu);
  settingsMenu.addSubMenu("Return", Images::img_menuReturn, &mainMenu);

  gunMenu.init(sideDisplay, &mainMenu);
  gunMenu.setParentMenu(&mainMenu);

  messageMenu.init(sideDisplay, &mainMenu, LaserTag::getNetworkManager()->getMessageQueue(), "Messages");
  messageMenu.setParentMenu(&mainMenu);

  debugMsgMenu.init(sideDisplay, &settingsMenu, LaserTag::getNetworkManager()->getDebugMessageQueue(), "Debug");
  debugMsgMenu.setParentMenu(&settingsMenu);

  nameMenu.init(sideDisplay, &settingsMenu);
  nameMenu.setParentMenu(&settingsMenu);
  nameMenu.setCallback(std::bind(&PlayerWrapper::setName, LaserTag::getPlayer(), std::placeholders::_1));

  adminPasswordMenu.init(sideDisplay, &settingsMenu);
  adminPasswordMenu.setParentMenu(&settingsMenu);
  adminPasswordMenu.setCallback(std::bind(&Networks::Network::tryMakeAdmin, std::placeholders::_1));

  adminMenu.init(sideDisplay);
  adminMenu.setParentMenu(&mainMenu);
  adminMenu.setRequiresAdmin(true);
  adminMenu.addSubMenu("Commands", Images::img_menuCommand, &commandMenu);
  adminMenu.addSubMenu("Cmd Type", Images::img_menuSettings, &adminCommandSendMethodMenu);
  adminMenu.addSubMenu("Return", Images::img_menuReturn, &mainMenu);

  commandMenu.init(sideDisplay);
  commandMenu.setParentMenu(&adminMenu);
  commandMenu.addSubMenu("Games", Images::img_menuCommand, &commandGamemodeMenu);
  commandMenu.addSubMenu("Player", Images::img_menuCommand, &commandPlayerMenu);
  commandMenu.addSubMenu("Teams", Images::img_menuCommand, &commandTeamMenu);
  commandMenu.addSubMenu("Weapons", Images::img_menuCommand, &commandWeaponsMenu);
  commandMenu.addSubMenu("Hardware", Images::img_menuCommand, nullptr);
  commandMenu.addSubMenu("Return", Images::img_menuReturn, &adminMenu);

  adminCommandSendMethodMenu.init(sideDisplay);
  adminCommandSendMethodMenu.setParentMenu(&adminMenu);
  adminCommandSendMethodMenu.addFunction("All", Images::img_menuCommand,
                                         std::bind(&Commands::CommandManager::setCmdTypeBroadcast,
                                                   LaserTag::getCommandManager()));
  adminCommandSendMethodMenu.addFunction("Single", Images::img_menuCommand,
                                         std::bind(&Commands::CommandManager::setCmdTypeSingle,
                                                   LaserTag::getCommandManager()));
  adminCommandSendMethodMenu.addFunction("Self", Images::img_menuCommand,
                                         std::bind(&Commands::CommandManager::setCmdTypeSelf,
                                                   LaserTag::getCommandManager()));
  adminCommandSendMethodMenu.addSubMenu("Return", Images::img_menuReturn, &adminMenu);

  commandGamemodeMenu.init(sideDisplay);
  commandGamemodeMenu.setParentMenu(&commandMenu);
  commandGamemodeMenu.addSubMenu("Games", Images::img_menuCommand, &gamesCommandMenu);
  commandGamemodeMenu.addSubMenu("Mods", Images::img_menuCommand, &gameModsCommandMenu);
  commandGamemodeMenu.addSubMenu("Return", Images::img_menuReturn, &commandMenu);

  commandWeaponsMenu.init(sideDisplay);
  commandWeaponsMenu.setParentMenu(&commandMenu);
  commandWeaponsMenu.addSubMenu("Types", Images::img_menuCommand, &weaponTypeCommandMenu);
  commandWeaponsMenu.addSubMenu("Groups", Images::img_menuCommand, &weaponGroupCommandMenu);
  commandWeaponsMenu.addSubMenu("Return", Images::img_menuReturn, &commandMenu);

  gamesCommandMenu.init(sideDisplay, &commandGamemodeMenu, "Gamemodes");
  gamesCommandMenu.setParentMenu(&commandGamemodeMenu);
  gameModsCommandMenu.init(sideDisplay, &commandGamemodeMenu, "Game Mods");
  gameModsCommandMenu.setParentMenu(&commandGamemodeMenu);


  commandTeamMenu.init(sideDisplay, &commandMenu, "Teams");
  commandTeamMenu.setParentMenu(&commandMenu);

  commandPlayerMenu.init(sideDisplay, &commandMenu, "Players");
  commandPlayerMenu.setParentMenu(&commandMenu);

  weaponTypeCommandMenu.init(sideDisplay, &commandWeaponsMenu, "Guns");
  weaponTypeCommandMenu.setParentMenu(&commandWeaponsMenu);

  weaponGroupCommandMenu.init(sideDisplay, &commandWeaponsMenu, "Gun Groups");
  weaponGroupCommandMenu.setParentMenu(&commandWeaponsMenu);

  display(true); // display the menu
}

void MenuManager::loop() {
  // loop function to refresh the menu

  if (millis() - lastMenuRefresh > MENU_REFRESH_TIME) {
    currentMenu->display(false);
    currentMenu->onRotaryTurned(0);
    lastMenuRefresh = millis();
  }
}