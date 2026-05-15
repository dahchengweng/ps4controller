#include "PS4ControllerManager.h"

ControllerPtr PS4ControllerManager::controller = nullptr;

void PS4ControllerManager::begin(bool forgetKeys) {
    BP32.setup(&PS4ControllerManager::onConnected, &PS4ControllerManager::onDisconnected);

    if (forgetKeys)
        BP32.forgetBluetoothKeys();

    BP32.enableVirtualDevice(false);
}

void PS4ControllerManager::update() {
    bool updated = BP32.update();
    if (!updated || !controller || !controller->isConnected())
        return;

    processButtons();
    processSticks();
}

bool PS4ControllerManager::isConnected() {
    return controller && controller->isConnected();
}

// ---------------------- Stick getters ----------------------

int PS4ControllerManager::leftX() { return controller ? controller->axisX() : 0; }
int PS4ControllerManager::leftY() { return controller ? controller->axisY() : 0; }
int PS4ControllerManager::rightX() { return controller ? controller->axisRX() : 0; }
int PS4ControllerManager::rightY() { return controller ? controller->axisRY() : 0; }

// ---------------------- LED & rumble ----------------------

void PS4ControllerManager::setLED(uint8_t r, uint8_t g, uint8_t b) {
    if (controller)
        controller->setColorLED(r, g, b);
}

void PS4ControllerManager::rumble(uint8_t weak, uint8_t strong, uint16_t durationMs) {
    if (controller)
        controller->playDualRumble(0, durationMs, weak, strong);
}

// ---------------------- Callback registration ----------------------

void PS4ControllerManager::onButtonEvent(void (*callback)(PS4Button, PS4ButtonEventType)) {
    buttonEventCallback = callback;
}

void PS4ControllerManager::onStickMove(void (*callback)(int, int, int, int)) {
    stickMoveCallback = callback;
}

// ---------------------- Static callbacks ----------------------

void PS4ControllerManager::onConnected(ControllerPtr ctl) {
    controller = ctl;
    Serial.println("PS4 Controller Connected");
}

void PS4ControllerManager::onDisconnected(ControllerPtr ctl) {
    if (controller == ctl) {
        controller = nullptr;
        Serial.println("PS4 Controller Disconnected");
    }
}

// ---------------------- Internal processing ----------------------

void PS4ControllerManager::processButtons() {
    if (!buttonEventCallback)
        return;

    uint32_t btn = controller->buttons();
    uint32_t misc = controller->miscButtons();
    uint32_t changed = (btn ^ lastButtons);

    auto emit = [&](PS4Button b, bool pressed) {
        if (pressed)
            buttonEventCallback(b, PS4ButtonEventType::Pressed);
        else
            buttonEventCallback(b, PS4ButtonEventType::Released);

        if (pressed)
            buttonEventCallback(b, PS4ButtonEventType::Held);
    };

    // ABXY (Cross, Circle, Square, Triangle)
    emit(PS4Button::Cross,    btn & BUTTON_A);
    emit(PS4Button::Circle,   btn & BUTTON_B);
    emit(PS4Button::Square,   btn & BUTTON_X);
    emit(PS4Button::Triangle, btn & BUTTON_Y);

    // L1 / R1 / L2 / R2 / L3 / R3
    emit(PS4Button::L1, btn & 0x0100);
    emit(PS4Button::R1, btn & 0x0200);
    emit(PS4Button::L2, btn & 0x0400);
    emit(PS4Button::R2, btn & 0x0800);
    emit(PS4Button::L3, btn & 0x1000);
    emit(PS4Button::R3, btn & 0x2000);

    // Share / Options / PS
    emit(PS4Button::Share,    misc & MISC_BUTTON_BACK);
    emit(PS4Button::Options,  misc & MISC_BUTTON_HOME);
    emit(PS4Button::PSButton, misc & MISC_BUTTON_SYSTEM);

    // Dpad
    uint8_t dpad = controller->dpad();
    emit(PS4Button::DpadUp,    dpad == DPAD_UP);
    emit(PS4Button::DpadDown,  dpad == DPAD_DOWN);
    emit(PS4Button::DpadLeft,  dpad == DPAD_LEFT);
    emit(PS4Button::DpadRight, dpad == DPAD_RIGHT);

    lastButtons = btn;
}

void PS4ControllerManager::processSticks() {
    if (!stickMoveCallback)
        return;

    int lx = controller->axisX();
    int ly = controller->axisY();
    int rx = controller->axisRX();
    int ry = controller->axisRY();

    if (lx != lastLX || ly != lastLY || rx != lastRX || ry != lastRY) {
        stickMoveCallback(lx, ly, rx, ry);
    }

    lastLX = lx;
    lastLY = ly;
    lastRX = rx;
    lastRY = ry;
}
