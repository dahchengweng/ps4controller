#pragma once
#include <Bluepad32.h>

enum class PS4Button {
    Cross,
    Circle,
    Square,
    Triangle,
    L1,
    R1,
    L2,
    R2,
    L3,
    R3,
    Options,
    Share,
    PSButton,   // ← 修正：避免與 ESP32 #define PS 衝突
    DpadUp,
    DpadDown,
    DpadLeft,
    DpadRight
};

enum class PS4ButtonEventType {
    Pressed,
    Released,
    Held
};

class PS4ControllerManager {
public:
    void begin(bool forgetKeys = false);
    void update();

    bool isConnected();

    // Stick getters
    int leftX();
    int leftY();
    int rightX();
    int rightY();

    // LED & rumble
    void setLED(uint8_t r, uint8_t g, uint8_t b);
    void rumble(uint8_t weak, uint8_t strong, uint16_t durationMs);

    // Event callbacks
    void onButtonEvent(void (*callback)(PS4Button, PS4ButtonEventType));
    void onStickMove(void (*callback)(int lx, int ly, int rx, int ry));

private:
    static void onConnected(ControllerPtr ctl);
    static void onDisconnected(ControllerPtr ctl);

    static ControllerPtr controller;

    void (*buttonEventCallback)(PS4Button, PS4ButtonEventType) = nullptr;
    void (*stickMoveCallback)(int, int, int, int) = nullptr;

    void processButtons();
    void processSticks();

    uint32_t lastButtons = 0;
    int lastLX = 0, lastLY = 0, lastRX = 0, lastRY = 0;
};
