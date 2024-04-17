/*
 * Created by Ed Fillingham on 15/04/2024.
 *
 * This class manages all the menus in the system.
*/


#include "MenuManager.h"
#include "../SideDisplay.h"

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
  mainMenu.addSubMenu("Msgs", Images::img_menuMessages, nullptr);
  mainMenu.addSubMenu("Guns", Images::img_menuGuns, nullptr);
  mainMenu.addSubMenu("Settings", Images::img_menuSettings, &settingsMenu);
  mainMenu.addSubMenu("Admin", Images::img_menuAdmin, nullptr);

  settingsMenu.init(sideDisplay);
  settingsMenu.addSubMenu("Name", Images::img_menuName, nullptr);
  settingsMenu.addSubMenu("Turn Off", Images::img_menuTurnOff, nullptr);
  settingsMenu.addSubMenu("Admin #", Images::img_menuAdmin, nullptr);
  settingsMenu.addSubMenu("Return", Images::img_menuReturn, &mainMenu);

  display(true); // display the menu
}
