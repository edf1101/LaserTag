/*
 * Created by Ed Fillingham on 12/04/2024.
 *
 * This class represents a basic gamemode in the Laser Tag system.
 * Other more complex gamemodes will inherit from this class and add their own functionality.
*/

#include "Gamemode.h"
#include "../LaserTag.h"

namespace Gamemodes {

    Gamemode::Gamemode(LaserTag *_mySystem) {
      mySystem = _mySystem;
      myPlayer = mySystem->getPlayer();
      displayHud = mySystem->getHudDisplay();
      displayHud->setInfoStateCounts(2); // 2 states: display name, display gun

      // Initialise the widgets after the constructor has got pointers for display player, etc
    }

    bool Gamemode::canFire() {
      // This checks if the gun can fire according to gamemode rules

      if (!started) return false; // If the game hasn't started, return false

      return true; // If passed all conditions, return true
    }

    void Gamemode::onPlayerDeath() {

    }

    void Gamemode::onPickupRespawn() {

    }

    void Gamemode::onPickupFlag() {

    }

    void Gamemode::onDropFlag() {

    }

    void Gamemode::drawHUD() {
    }


    std::string Gamemode::getName() {
      return name;
    }


    void Gamemode::loop() {
      // This function is called each time the main loop is called

      // update the HUD every so often
      if (millis() - lastHudAutoUpdate > HUD_UPDATE_INTERVAL) {
        lastHudAutoUpdate = millis();
        drawHUD();
      }
    }

    void Gamemode::setGamePauseState(bool paused) {
      this->started = !paused;
    }

    bool Gamemode::canTakeDamage(int shooterUnitnum) {

      if (!started) return false; // If the game hasn't started, return false

      // TODO have some logic here to check teams

      return true; // If passed all conditions, return true
    }

    Player Gamemode::getPlayerTemplate() {
      // This template is used to reset the players to a default state when it enters a new gamemode

      Player playerTemplate = {
              .unitnum = -1, // irrelevant as this field doesn't copy from the template
              .team = 0,// irrelevant as this field doesn't copy from the template
              .name = "Player",// irrelevant as this field doesn't copy from the template
              .revives = 3,
              .health = 100,
              .kills = 0,
              .carryingFlag = false,
              .gunIndex = 0 // 0 should be default gun (AR)
      };
      return playerTemplate;
    }

    void Gamemode::loadGameDetails(JsonDocument gameDetails) {
      // recreate the details saved by getGameDetails() to load the game state
      started = gameDetails["started"];
    }

    JsonDocument Gamemode::getGameDetails() {
      // Return all important details about this gamemode so it can be recreated in loadGameDetails()

      JsonDocument gameDetails;
      gameDetails["started"] = started;

      return gameDetails;
    }

    void Gamemode::onHitConfirm(int victimUnitnum, bool kill) {
      // This function is called when a hit/kill is confirmed.

      // in this base game bit all we do is increment the kills.
      if (kill)// if it was a kill not just a hit
        LaserTag::getPlayer()->setKills(LaserTag::getPlayer()->getKills() + 1);
    }
}