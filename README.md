# HomeKit Garage Door Controller

**HomeKit garage door controller for standard garage door motors**

This project implements a HomeKit-compatible garage door controller using an ESP32 microcontroller and the HomeSpan library. It enables remote control and status monitoring of your garage door with Apple HomeKit.

## Features
- **Status Detection:** Real-time detection of garage door states (open, closed, opening, closing).
- **Door Status:** Detects when the garage door opens/closes from a different source (e.g. remote control, wall button, keypad).
- **Movement Timeout:** If door is opening/closing for over 20 seconds, system assumes door is open. Helpful for when the door is partially open.

## How It Works
The system uses an ESP32 microcontroller to manage a relay and monitor the garage door's operational state:
- **Relay Control:** The relay pin (GPIO 35) triggers the garage door motor.
- **Status Monitoring:** Two status pins (GPIO 21 for closed sensor, GPIO 36 for open sensor) monitor the garage door's position.
- **Dual Sensor Logic:** The system determines the garage state based on the combination of sensor readings:
  - If closed sensor is LOW and open sensor is HIGH: door is CLOSED
  - If closed sensor is HIGH and open sensor is LOW: door is OPEN
  - If both are HIGH: door is in motion (opening or closing)

The `DEV_GARAGE.h` class implements:
- `update()` – Triggered by HomeKit to open/close the garage door.
- `loop()` – Continuously monitors the garage door's state based on the input pins.

## Hardware Requirements
- ESP32 microcontroller
- Relay module (for garage door control)
- Two door position sensors (reed switches)

## Wiring

```
   +-------------+                    +--------------+
   |             |                    |              |
   |    ESP32    |                    | RELAY MODULE |
   |             |                    |              |
   | GPIO 35 o---+------------------->o IN           |
   |             |                    |              |
   | 5V      o---+------------------->o VCC          |
   |             |                    |              |
   | GND     o---+------------------->o GND          |
   |             |                    |              |
   |             |                    | COM -------> To Door GND
   |             |                    | NO --------> To Door TRIG
   |             |                    |              |
   |             |                    +--------------+
   |             |        
   |             |        
   |             |                    +--------------+
   | GPIO 21 o<--+--------------------o OUT          |
   |             |                    |              |     (completes 
   | GND     o---+------------------->o GND          |     circuit when 
   |             |                    |              |     magnet is near)
   |             |                    | CLOSED SENSOR|
   |             |                    +--------------+
   |             |        
   |             |        
   |             |                    +--------------+
   | GPIO 36 o<--+--------------------o OUT          |
   |             |                    |              |      (completes
   | GND     o---+------------------->o GND          |      circuit when
   |             |                    |              |      magnet is away)
   |             |                    | OPEN SENSOR  |
   +-------------+                    +--------------+
```

## Software Requirements
- [HomeSpan Library](https://github.com/HomeSpan/HomeSpan)
- Arduino IDE (for programming the ESP32)

## Configuration
- **Wi-Fi:** Set credentials in `homekitGarage.ino`.
- **HomeKit Pin:** Default pairing pin is `92747402`.
- **Pins:** Adjust `closedSensorPin`, `openSensorPin`, and `relayPin` if necessary.
  
## Installation
1. Install the HomeSpan library.
2. Download and open both `homekitGarage.ino` and `DEV_GARAGE.h` in an IDE.
3. Configure Wi-Fi credentials, HomeKit pairing code in `homekitGarage.ino`.
4. Upload the files to your ESP32.
5. Pair the device with HomeKit using the code.

## Future Improvements
- **Obstruction Detection:** Currently not implemented.

## License
This project is licensed under the [Creative Commons BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)

