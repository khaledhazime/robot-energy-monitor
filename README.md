# Robot Energy Monitor

## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)


## About <a name = "about"></a>

ESP32-based robot energy monitor. It monitors and publish into a web server information as current, voltage and power for each robot's module.

## Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your own robot for development and testing purposes.

### Prerequisites

- [Latest Arduino IDE](arduino.cc/en/Main/Software)
- [ESP32 Add-on](#esp32)
- [Arduino JSON Library](#arduino_json_library)
- [EmonLib Library](#arduino_emonlib_library)

### Installing
#### ESP32 Add-on <a name = "esp32"></a>

To install the ESP32 board in your Arduino IDE, follow these next instructions:
1. In your Arduino IDE go to **File > Preferences** 
![arduino-open-preferences](https://github.com/khaledhazime/robot-energy-monitor/blob/main/config/img/arduino-open-preferences.png)

2. Enter the following into the "Additional Board Manager URLs" field:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
Then, click the "OK" button:
![arduino-preferences](https://github.com/khaledhazime/robot-energy-monitor/blob/main/config/img/arduino-preferences.png)

3. Open the Boards Manager. Go to **Tools > Board > Boards Manager...**
![arduino-boards-manager](https://github.com/khaledhazime/robot-energy-monitor/blob/main/config/img/arduino-boards-manager.png)

4. Search for **ESP32** and press install button for the "**ESP32 by Expressif Systems**"
![arduino-esp32-board-installation](https://github.com/khaledhazime/robot-energy-monitor/blob/main/config/img/arduino-esp32-board-installation.png)

#### Arduino_JSON Library <a name = "arduino_json_library"></a>
You also need to install the Arduino_JSON library. You can install this library in the Arduino IDE Library Manager. Just go to **Sketch > Include Library > Manage Libraries** and search for "**Arduino_JSON**"
![arduino-json-library-installation](https://github.com/khaledhazime/robot-energy-monitor/blob/main/config/img/arduino-json-library-installation.png)

arduino-emonlib-library-installation
#### EmonLib Library <a name = "emonlib_library"></a>
You also need to install the EmonLib library. You can install this library in the Arduino IDE Library Manager. Just go to **Sketch > Include Library > Manage Libraries** and search for "**EmonLib**"
![arduino-emonlib-library-installation](https://github.com/khaledhazime/robot-energy-monitor/blob/main/config/img/arduino-emonlib-library-installation.png)

## Usage <a name = "usage"></a>

1. Create a new project in your Arduino IDE.
2. Select the **ESP32** board.
3. Set up Wifi connection.
4. Set up constants for the modules.
5. Upload the project to your ESP32.
