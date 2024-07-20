/*
 * Created by Ed Fillingham on 13/04/2024.
 *
 * This widget is a small progress bar (horizontal) that can be displayed on the HUD.
 * Used for things like health bars, loading bars etc.
*/

#include "HudWidgetProgress.h"

using namespace HudWidgets;

void HudWidgetProgress::setProgress(int _progress) {
  progress = _progress;
}

void HudWidgetProgress::erase() {
  // Erase the widget from the screen
  if (!displayAssigned) {
    return;
  }

  int x = (64-barWidth)/2;
  int y = yCoordinate;

  display->getDisplay()->fillRect(x, y, barWidth, barHeight, SSD1306_BLACK);
}

void HudWidgetProgress::draw(bool force) {
  // Draw the widget to the screen
  if (!displayAssigned) {
    return;
  }

  if (progress == lastProgress && !force) {
    return;
  }

  erase();


  int x = (64-barWidth)/2;
  int y = yCoordinate;

  // draw new bar outline
  display->getDisplay()->drawRect(x, y, barWidth, barHeight, SSD1306_WHITE);

  // fill in the progress
  int progressWidth = (barWidth * progress) / 100;
  display->getDisplay()->fillRect(x, y, progressWidth, barHeight, SSD1306_WHITE);

  lastProgress = progress;
}

