/*
 * Created by Ed Fillingham on 20/07/2024.
 *
 * This is a proprietary logger class that primarily logs messages to the serial port.
 * It also can be used to stop and power off the device if a fatal error occurs.
*/

#include "Logger.h"
#include "../config.h"
#include "../LaserTag.h"

void Logger::init(bool _serialOn, unsigned long _baudRate, LogLevel _loggerLevel) {
  // Initialises the logger

  serialOn = _serialOn;
  loggerLevel = _loggerLevel;

  if (serialOn) {
    Serial.begin(_baudRate);
  }
}

void Logger::log(LogLevel level, std::string message) {
  // Logs a message to the system

  if (level < loggerLevel) { // if the level is less than the logger level, return
    return;
  }

  std::string logMessage = "LOG ";

  switch (level) { // add the log type to the start of the string
    case LogLevel::DETAIL:
      logMessage += "DETAIL: ";
      break;
    case LogLevel::INFO:
      logMessage += "INFO: ";
      break;
    case LogLevel::ERROR:
      logMessage += "ERROR: ";
      break;
    case LogLevel::FATAL:
      logMessage += "FATAL: ";
      break;
  }
  logMessage += message; // add the message to the string

  if (serialOn) { // if the serial port is on, print the message
    Serial.println(logMessage.c_str());
  }

  logBuffer.pushMessage(message); // add the message to the buffer

  if (level == LogLevel::FATAL) { // if the level is fatal, power off the device

    // display the fatal error message on the screen.
    Adafruit_ST7735 *tft = LaserTag::getSideDisplay()->getRawDisplay();

    tft->setTextWrap(false);
    tft->fillScreen(ST77XX_BLACK);
    tft->setCursor(10, 10);
    tft->setTextColor(ST77XX_RED);
    tft->setTextSize(1);
    tft->println(message.c_str());

    delay(20 * 1000);
    // power off the device
    digitalWrite(POWER_HOLD_PIN, LOW);
  }
}

Networks::MessageQueue *Logger::getLogBuffer() {
  // Returns the log buffer

  return &logBuffer;
}


