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

## Controller → Bluepad32 → Manager → Callback Flow

```mermaid
flowchart TD

    subgraph Controller["Game Controller"]
        A1[Button Input]
        A2[Stick Input]
        A3[System Input]
    end

    subgraph Bluepad32["Bluepad32 Core"]
        B1[Receive Data]
        B2[Parse Buttons]
        B3[Parse Sticks]
        B4[Connection Events]
        B5[Data Update]
    end

    subgraph Manager["Controller Manager"]
        C1[Store Pointer]
        C2[Manager Update]
        C3[Handle Buttons]
        C4[Handle Sticks]
        C5[Detect Events]
        C6[Call Button Callback]
        C7[Call Stick Callback]
    end

    subgraph UserCode["User Application"]
        D1[Register Button Callback]
        D2[Register Stick Callback]
        D3[User Button Handler]
        D4[User Stick Handler]
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
