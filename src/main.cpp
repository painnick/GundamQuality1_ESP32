#include <Arduino.h>

#include "esp_log.h"

#include "ESP32Servo.h"

#define MAIN_TAG "Main"

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_NECK_SERVO 32
#define PIN_ARM_SERVO 33

Servo neckServo;
Servo armServo;

void setup() {
#ifdef DEBUG
    ESP_LOGI(MAIN_TAG, "Setup...");
#endif
    neckServo.attach(PIN_NECK_SERVO);
    neckServo.write(0);

    armServo.attach(PIN_ARM_SERVO);
    armServo.write(30);

    delay(1000 * 5);
}

void loop() {
    for(auto i = 30; i > -1; i -= 5) {
        armServo.write(i);
        delay(100);
    }

    delay(1000 * 1);
    
    for(auto i = 0; i < 90; i += 5) {
        neckServo.write(i);
        delay(50);
    }

    delay(1000 * 2);

    for(auto i = 90; i > -1; i -= 5) {
        neckServo.write(i);
        delay(50);
    }

    delay(1000 * 2);

    for(auto i = 0; i < 30; i += 5) {
        armServo.write(i);
        delay(100);
    }

    delay(1000 * 10);
}
