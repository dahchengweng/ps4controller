# ps4controller
ps4controller used for ESP32, inspired by https://github.com/ricardoquesada/bluepad32

# PS4 Controller Manager for ESP32 (Bluepad32)

A clean, modular wrapper for using PS4 controllers on ESP32 via Bluepad32.
This library encapsulates pairing, connection handling, button events, stick events, and LED/rumble control into a single class: PS4ControllerManager.

Designed for projects that require clean architecture, event-driven input handling, and easy integration with robotics or embedded systems.

---

## Features

- Single PS4 controller support
- Event-driven architecture  
  - Button events: Pressed / Released / Held  
  - Stick movement events (LX, LY, RX, RY)
- PS4 official button naming
- LED color control
- Rumble (vibration) control
- Clean .ino file with callback registration
- Fully compatible with Bluepad32 Arduino 4.x

---

## Project Structure

/your-project  
│── PS4ControllerManager.h  
│── PS4ControllerManager.cpp  
│── main.ino  
└── README.md  

---

## Installation

1. Install ESP32 Bluepad32 Board Package  
   Board Manager URL:  
   https://bluepad32.github.io/arduino/package_esp32_bluepad32_index.json

2. Select board:  
   ESP32 Dev Module (Bluepad32)

3. Place the following files in your project folder:
   - PS4ControllerManager.h
   - PS4ControllerManager.cpp
   - main.ino

4. Compile & upload.

---

## Usage Example

main.ino

