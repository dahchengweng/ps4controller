#include <Arduino.h>
#include "PS4ControllerManager.h"

PS4ControllerManager ps4;

// ---------------------- Callback functions ----------------------

void onPS4Button(PS4Button btn, PS4ButtonEventType type) {
    Serial.printf("Button %d event %d\n", (int)btn, (int)type);
}

void onPS4Stick(int lx, int ly, int rx, int ry) {
    Serial.printf("LX=%d LY=%d RX=%d RY=%d\n", lx, ly, rx, ry);
}

// ---------------------- Arduino setup ----------------------

void setup() {
    Serial.begin(115200);

    ps4.begin(true);

    ps4.onButtonEvent(onPS4Button);
    ps4.onStickMove(onPS4Stick);
}

// ---------------------- Arduino loop ----------------------

void loop() {
    ps4.update();
    delay(10);
}
