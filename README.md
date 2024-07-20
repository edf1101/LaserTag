# LaserTag

## Introduction
This repository contains all the code, designs and tools needed to build (both physically and in code) my laser tag system.
The system is designed to be uploaded easily with [Arduino IDE](https://www.arduino.cc/) compatible builds and coded 
in a [platformio](https://platformio.org/) environment.

## Hardware
The main driver is an ESP32.
- Other components can be found [here](hardware/BOM_LaserTag.csv).
- Schematics can be found [here](hardware/Schematic_LaserTag.pdf).

## Software
### Libraries needed
_The last tested and working version numbers are displayed next to the library. These libraries may still require
dependencies_

- Adafruit MCP23017 Arduino Library 2.3.2 
- Adafruit SSD1306 2.5.9
- Adafruit ST7735 and ST7789 Library 1.10.3
- ArduinoJson 7.0.4
- TaskScheduler 3.7.0
- AsyncTCP 1.1.1
- ESP8266Audio 1.9.7

### Installation
#### Basic Setup (Arduino IDE)
To upload the code without doing any major modifications it is easiest to use the Arduino IDE:
1. Install the Arduino IDE and ESP32 board manager.
2. Download the simple code from the releases section.
3. Open the code in the Arduino IDE.
4. Go to the library manager and install the libraries listed above.
5. Select the correct board settings and port (for more info check the [platformio.ini](platformio.ini) file).
6. Upload the code.

#### Advanced Setup (Platformio)
To use the code in a platformio environment:
1. Clone the repository.
2. Open the code in a platformio environment.
3. Build and upload the code.

## Laser Tagger Usage
A guide on how to use the laser tagger can be found [here](res/Usage.md).



