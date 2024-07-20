/*
 * Created by Ed Fillingham on 20/07/2024.
*/

#include "Hardware.h"
#include "Logger/Logger.h"

void Hardware::init() {
  // Initlises the hardware this class controls

  // Turn on the power latch to the gun,
  // do this as fast as possible to prevent the gun from turning off when the player lets go of the trigger.
  pinMode(POWER_HOLD_PIN, OUTPUT);
  digitalWrite(POWER_HOLD_PIN, HIGH);

  Logger::log(Logger::LogLevel::INFO, "Searching for MCP");

//  if (!mcp.begin_I2C()) {
//    Logger::log(Logger::LogLevel::FATAL, "No MCP found");
//  }
//  Logger::log(Logger::LogLevel::INFO, "MCP found");

}

void Hardware::loop() {
  // Loops the hardware objects this class controls (used for powering off only)

  if (turnedOff) {
    if (millis() - turnOffTime > turnOffDelay) {
      // turn off the gun
      digitalWrite(POWER_HOLD_PIN, LOW);
    }

  }
}

void Hardware::pinModeExp(uint8_t pin, uint8_t mode) {
  // Set the mode of a pin on the GPIO expander

  mcp.pinMode(pin, mode);
}

bool Hardware::digitalReadExp(uint8_t pin) {
  // Read the value of a pin on the GPIO expander

  return mcp.digitalRead(pin);

}

void Hardware::digitalWriteExp(uint8_t pin, uint8_t value) {
  // Write a value to a pin on the GPIO expander

  mcp.digitalWrite(pin, value);
}

void Hardware::turnOffSystem(unsigned long delay) {
  // turn off the gun in "delay" milliseconds

  if (!turnedOff) {
    turnedOff = true;
    turnOffTime = millis();
    turnOffDelay = delay;
  }

}

uint8_t Hardware::findOLEDAddress() {
  int possibleAddresses[] = {0x78, 0x79, 0x7A, 0x7B,0x3C,0x3D};

  uint8_t foundDevice = 0;
  Wire.begin();
  for (byte address : possibleAddresses) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      foundDevice = address;
    }

  }
  Wire.end();

  // if found device = 0 throw an error

  return foundDevice;
}
