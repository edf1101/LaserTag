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
  mainMenu.addSubMenu("Scores", Images::img_menuLeaderboard, nullptr);
  mainMenu.addSubMenu("Msgs", Images::img_menuMessages, &messageMenu);
  mainMenu.addSubMenu("Guns", Images::img_menuGuns, &gunMenu);
  mainMenu.addSubMenu("Settings", Images::img_menuSettings, &settingsMenu);
  mainMenu.addSubMenu("Admin", Images::img_menuAdmin, &adminMenu);

  settingsMenu.init(sideDisplay);
  settingsMenu.setParentMenu(&mainMenu);
  settingsMenu.addSubMenu("Name", Images::img_menuName, &nameMenu);
  settingsMenu.addFunction("Turn Off", Images::img_menuTurnOff, std::bind(&LaserTag::turnOff));
  settingsMenu.addSubMenu("Admin #", Images::img_menuAdmin, &adminPasswordMenu);
  settingsMenu.addSubMenu("Debug", Images::img_menuMessages, &debugMsgMenu);
  settingsMenu.addSubMenu("Return", Images::img_menuReturn, &mainMenu);

  gunMenu.init(sideDisplay, &mainMenu);
  gunMenu.setParentMenu(&mainMenu);

  messageMenu.init(sideDisplay, &mainMenu, LaserTag::getNetworkManager()->getMessageQueue());
  messageMenu.setParentMenu(&mainMenu);

  debugMsgMenu.init(sideDisplay, &settingsMenu, LaserTag::getNetworkManager()->getDebugMessageQueue());
  debugMsgMenu.setParentMenu(&settingsMenu);

  nameMenu.init(sideDisplay, &settingsMenu);
  nameMenu.setParentMenu(&settingsMenu);
  nameMenu.setCallback(std::bind(&LaserTag::setPlayerName, std::placeholders::_1));

  adminPasswordMenu.init(sideDisplay, &settingsMenu);
  adminPasswordMenu.setParentMenu(&settingsMenu);
  adminPasswordMenu.setCallback(std::bind(&Networks::Network::tryMakeAdmin, std::placeholders::_1));

  adminMenu.init(sideDisplay);
  adminMenu.setParentMenu(&mainMenu);
  adminMenu.setRequiresAdmin(true);
  adminMenu.addSubMenu("Commands", Images::img_menuCommand, &commandMenu);
  adminMenu.addSubMenu("Return", Images::img_menuReturn, &mainMenu);

  commandMenu.init(sideDisplay);
  commandMenu.setParentMenu(&adminMenu);
  commandMenu.addSubMenu("Games", Images::img_menuCommand, &commandGamemodeMenu);
  commandMenu.addSubMenu("Player", Images::img_menuCommand, nullptr);
  commandMenu.addSubMenu("Teams", Images::img_menuCommand, nullptr);
  commandMenu.addSubMenu("Weapons", Images::img_menuCommand, &commandWeaponsMenu);
  commandMenu.addSubMenu("Return", Images::img_menuReturn, &adminMenu);

  commandGamemodeMenu.init(sideDisplay);
  commandGamemodeMenu.setParentMenu(&commandMenu);
  commandGamemodeMenu.addSubMenu("Games", Images::img_menuCommand, &gamesCommandMenu);
  commandGamemodeMenu.addSubMenu("Mods", Images::img_menuCommand, nullptr);
  commandGamemodeMenu.addSubMenu("Return", Images::img_menuReturn, &commandMenu);

  commandWeaponsMenu.init(sideDisplay);
  commandWeaponsMenu.setParentMenu(&commandMenu);
  commandWeaponsMenu.addSubMenu("Types", Images::img_menuCommand, nullptr);
  commandWeaponsMenu.addSubMenu("Groups", Images::img_menuCommand, nullptr);
  commandWeaponsMenu.addSubMenu("Return", Images::img_menuReturn, &commandMenu);

  gamesCommandMenu.init(sideDisplay, &commandGamemodeMenu, "Test");


  display(true); // display the menu
}
