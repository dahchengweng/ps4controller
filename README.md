# ps4controller
ps4controller used for esp32 , and inspired by https://github.com/ricardoquesada/bluepad32

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

#include <Arduino.h>
#include "PS4ControllerManager.h"

PS4ControllerManager ps4;

// Button callback
void onPS4Button(PS4Button btn, PS4ButtonEventType type) {
    Serial.printf("Button %d event %d\n", (int)btn, (int)type);
}

// Stick callback
void onPS4Stick(int lx, int ly, int rx, int ry) {
    Serial.printf("LX=%d LY=%d RX=%d RY=%d\n", lx, ly, rx, ry);
}

void setup() {
    Serial.begin(115200);

    ps4.begin(true);  // true = forget Bluetooth keys

    ps4.onButtonEvent(onPS4Button);
    ps4.onStickMove(onPS4Stick);
}

void loop() {
    ps4.update();
    delay(10);
}

---

## Supported Buttons

PS4 Button → Enum Name

Cross     → PS4Button::Cross  
Circle    → PS4Button::Circle  
Square    → PS4Button::Square  
Triangle  → PS4Button::Triangle  
L1 / R1   → PS4Button::L1, PS4Button::R1  
L2 / R2   → PS4Button::L2, PS4Button::R2  
L3 / R3   → PS4Button::L3, PS4Button::R3  
Share     → PS4Button::Share  
Options   → PS4Button::Options  
PS Button → PS4Button::PSButton  
Dpad      → Up / Down / Left / Right  

---

## API Overview

Initialization:
void begin(bool forgetKeys = false);

Update loop:
void update();

Connection status:
bool isConnected();

Stick values:
int leftX();
int leftY();
int rightX();
int rightY();

LED control:
void setLED(uint8_t r, uint8_t g, uint8_t b);

Rumble:
void rumble(uint8_t weak, uint8_t strong, uint16_t durationMs);

Register callbacks:
void onButtonEvent(void (*callback)(PS4Button, PS4ButtonEventType));
void onStickMove(void (*callback)(int lx, int ly, int rx, int ry));

---

## Controller → Bluepad32 → Manager → Callback 流程圖

```mermaid
flowchart TD

    subgraph Controller["Game Controller"]
        A1[Button Input]
        A2[Stick Input]
        A3[System Buttons]
    end

    subgraph Bluepad32["Bluepad32 Library"]
        B1[Receive Bluetooth Data]
        B2[Parse Button Bitmask]
        B3[Parse Stick Axes]
        B4[onConnected / onDisconnected]
        B5[update() returns new data]
    end

    subgraph Manager["Controller Manager"]
        C1[Store ControllerPtr]
        C2[update()]
        C3[processButtons()]
        C4[processSticks()]
        C5[Detect Press/Release/Hold]
        C6[Trigger Button Callback]
        C7[Trigger Stick Callback]
    end

    subgraph UserCode["User Code"]
        D1[Register Button Callback]
        D2[Register Stick Callback]
        D3[onButtonEvent()]
        D4[onStickEvent()]
    end

    A1 --> B1
    A2 --> B1
    A3 --> B1

    B1 --> B2
    B1 --> B3
    B1 --> B4
    B1 --> B5

    B4 --> C1
    B5 --> C2

    C2 --> C3
    C2 --> C4

    C3 --> C5
    C5 --> C6

    C4 --> C7

    C6 --> D3
    C7 --> D4

    D1 --> C6
    D2 --> C7





## Notes

- This library is designed for Bluepad32 Arduino 4.x.
- Button bitmask definitions differ between versions; this implementation uses the correct mapping for 4.x.
- Only one controller is supported in this version.
- If your controller fails to reconnect, call begin(true) to clear Bluetooth keys.

---

## License (MIT)

MIT License

Copyright (c) 2026

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...

---

## Author

Developed by 大程  
For robotics, education, and embedded system projects.
