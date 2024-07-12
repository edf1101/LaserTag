/*
 * Created by Ed Fillingham on 08/07/2024.
 *
 * This widget is used to display player information on the side display. Primarily on the leaderboard
*/

#include "SideWidgetPlayerInfo.h"
#include "../../SideDisplay.h"
#include "../../../../Weapons/WeaponsManager.h"

namespace SideWidgets {

    SideWidgetPlayerInfo::SideWidgetPlayerInfo(int yStart) : SideWidget(yStart, 1) {
      // Constructor for the class

      this->width = 158; // rectangles are 160px wide and have 1px border
      this->height = 20; // rectangles are 22px high and have 1px border

    }

    void SideWidgetPlayerInfo::setStatus(Player *newPlayer, int newRank) {
      // Set the status of the player

      player = newPlayer;
      rank = newRank;
      playerAssigned = true;
    }

    void SideWidgetPlayerInfo::setStatus() {
      // set a blank status

      playerAssigned = false;
    }

    void SideWidgetPlayerInfo::draw(bool force) {
      // Draw the widget to the screen

      if (!displayAssigned) return; // If the display hasn't been assigned, return

      if (!playerAssigned) { // If no player has been assigned, erase the widget
        if (force)
          erase();
        return;
      }

      Adafruit_ST7735 *rawDisplay = myDisplay->getRawDisplay();
      rawDisplay->setTextSize(1); // Set the text size
      rawDisplay->setTextWrap(false); // Wrap the text

      if (lastWidgetHighlighted != widgetHighlighted)
        force = true;

      // This is drawing the rank number
      int currentRank = rank;
      if (currentRank != lastRank || force) {
        // draw over old one in black
        rawDisplay->setTextColor(ST7735_BLACK); // Set the text colour
        rawDisplay->setCursor(xStart + 2, yStart + 7); // Set the cursor to the top left corner of the widget
        rawDisplay->print((std::to_string(lastRank + 1) + ".").c_str()); // Print the text

        rawDisplay->setTextColor(widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Set the text colour
        rawDisplay->setCursor(xStart + 2, yStart + 7); // Set the cursor to the top left corner of the widget
        rawDisplay->print((std::to_string(currentRank + 1) + ".").c_str()); // Print the text
        lastRank = currentRank;
        lastWidgetHighlighted = widgetHighlighted;
      }

      // draw the separator between rank and name
      if (force) {
        lastWidgetHighlighted = widgetHighlighted;
        rawDisplay->fillRect(xStart + 19, yStart + 1, 2, 20,
                             widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Draw the divider
      }

      // This is drawing the name
      std::string currentName = player->name;
      if (currentName != lastName || force) {
        // draw over old one in black
        rawDisplay->setTextColor(ST7735_BLACK); // Set the text colour
        rawDisplay->setCursor(xStart + 23, yStart + 7); // Set the cursor to the top left corner of the widget
        std::string tempName = lastName.substr(0, 7);
        rawDisplay->print(tempName.c_str()); // Print the text

        // draw new one
        rawDisplay->setTextColor(widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Set the text colour
        rawDisplay->setCursor(xStart + 23, yStart + 7); // Set the cursor to the top left corner of the widget
        tempName = currentName.substr(0, 7);
        rawDisplay->print(tempName.c_str()); // Print the text
        lastName = currentName;
        lastWidgetHighlighted = widgetHighlighted;
      }

      // draw the separator between name and health
      if (force) {
        rawDisplay->fillRect(xStart + 66, yStart + 1, 2, 20,
                             widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Draw the divider
        lastWidgetHighlighted = widgetHighlighted;

      }

      // This is drawing the revives & health
      int currentRevives = player->revives;
      int currentHealth = player->health;
      if (force || (lastRevives != currentRevives || lastHealth != currentHealth)) {
        // draw over old one in black
        rawDisplay->setTextColor(ST7735_BLACK); // Set the text colour
        rawDisplay->setCursor(xStart + 70, yStart + 7); // Set the cursor to the top left corner of the widget
        rawDisplay->print(lastRevives); // Print the text
        rawDisplay->write(0x03); // Print the heart symbol
        rawDisplay->print((" " + std::to_string(lastHealth) + "%").c_str()); // Print the text

        rawDisplay->setTextColor(widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Set the text colour
        rawDisplay->setCursor(xStart + 70, yStart + 7); // Set the cursor to the top left corner of the widget
        rawDisplay->print(currentRevives); // Print the text
        rawDisplay->write(0x03); // Print the heart symbol
        rawDisplay->print((" " + std::to_string(currentHealth) + "%").c_str()); // Print the text

        lastRevives = currentRevives;
        lastHealth = currentHealth;
        lastWidgetHighlighted = widgetHighlighted;
      }

      // draw the separator between name and health
      if (force) {
        rawDisplay->fillRect(xStart + 119, yStart + 1, 2, 20,
                             widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Draw the divider
        lastWidgetHighlighted = widgetHighlighted;
      }

      // This is drawing the kills
      int currentKills = player->kills;
      if (lastKills != currentKills || force) {
        // draw over old one in black
        rawDisplay->setTextColor(ST7735_BLACK); // Set the text colour
        rawDisplay->setCursor(xStart + 123, yStart + 2); // Set the cursor to the top left corner of the widget
        rawDisplay->print(("KLS " + std::to_string(lastKills)).c_str()); // Print the text

        // draw new one
        rawDisplay->setTextColor(widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Set the text colour
        rawDisplay->setCursor(xStart + 123, yStart + 2); // Set the cursor to the top left corner of the widget
        rawDisplay->print(("KLS " + std::to_string(currentKills)).c_str()); // Print the text

        lastKills = currentKills;
        lastWidgetHighlighted = widgetHighlighted;
      }

      // draw the GUN
      std::string currentGun = WeaponsManager::getGun(player->gunIndex).getAcronym();;

      if (currentGun != lastGun || force) {
        // draw over old one in black
        rawDisplay->setTextColor(ST7735_BLACK); // Set the text colour
        rawDisplay->setCursor(xStart + 127, yStart + 11); // Set the cursor to the top left corner of the widget
        rawDisplay->print(lastGun.c_str()); // Print the text

        rawDisplay->setTextColor(widgetHighlighted ? TFT_PRIMARY_COLOUR : TFT_SECONDARY_COLOUR); // Set the text colour
        rawDisplay->setCursor(xStart + 127, yStart + 11); // Set the cursor to the top left corner of the widget
        rawDisplay->print(currentGun.c_str()); // Print the text

        lastGun = currentGun;
        lastWidgetHighlighted = widgetHighlighted;
      }

    }

    void SideWidgetPlayerInfo::setHighlight(bool highlight) {
      // Set the highlight of the widget

      widgetHighlighted = highlight;
    }

    void SideWidgetPlayerInfo::erase() {
      // Erase the widget from the screen

      Adafruit_ST7735 *rawDisplay = myDisplay->getRawDisplay();
      rawDisplay->fillRect(xStart, yStart + 1, width, height, ST7735_BLACK);
    }


} // SideWidgets