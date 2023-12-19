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

#define NECK_ANGLE_START 90
#define NECK_ANGLE_1 180
#define NECK_ANGLE_SHAKE1 30
#define NECK_ANGLE_SHAKE2 120
#define NECK_ANGLE_SHAKE3 135


#define ARM_ANGLE_START 0
#define ARM_ANGLE_1 16
#define ARM_ANGLE_2 20

void shakingHead();
void glance();

void setup() {
#ifdef DEBUG
    ESP_LOGI(MAIN_TAG, "Setup...");
#endif
    neckServo.attach(PIN_NECK_SERVO);
    neckServo.write(NECK_ANGLE_START);

    armServo.attach(PIN_ARM_SERVO);
    armServo.write(ARM_ANGLE_2);

    delay(1000 * 5);
}

void loop() {
    for (auto i = ARM_ANGLE_1; i >= ARM_ANGLE_START; i -= 3) {
        armServo.write(i);
        delay(100);
    }

    delay(1000 * 1);

    for (auto i = NECK_ANGLE_START; i <= NECK_ANGLE_1; i += 5) {
        neckServo.write(i);
        delay(50);
    }

    delay(1000 * 2);

    for (auto i = NECK_ANGLE_1; i >= NECK_ANGLE_START; i -= 5) {
        neckServo.write(i);
        delay(50);
    }

    delay(1000 * 1);

    shakingHead();

    delay(1000 * 1);

    for (auto i = ARM_ANGLE_START; i <= ARM_ANGLE_1; i += 3) {
        armServo.write(i);
        delay(100);
    }

    delay(1000 * 3);

    glance();

    delay(1000 * 1);

    for (auto i = ARM_ANGLE_1; i <= ARM_ANGLE_2; i += 3) {
        armServo.write(i);
        delay(100);
    }

    delay(1000 * 7);
}


void shakingHead() {
    for (auto i = NECK_ANGLE_START; i >= NECK_ANGLE_SHAKE1; i -= 5) {
        neckServo.write(i);
        delay(30);
    }

    for (auto i = NECK_ANGLE_SHAKE1; i <= NECK_ANGLE_SHAKE2; i += 5) {
        neckServo.write(i);
        delay(30);
    }

    for (auto i = NECK_ANGLE_SHAKE2; i >= NECK_ANGLE_START; i -= 5) {
        neckServo.write(i);
        delay(30);
    }
}


void glance() {
    for (auto i = NECK_ANGLE_START; i <= NECK_ANGLE_SHAKE3; i += 3) {
        neckServo.write(i);
        delay(50);
    }

    delay(1000);

    for (auto i = NECK_ANGLE_SHAKE3; i >= NECK_ANGLE_START; i -= 3) {
        neckServo.write(i);
        delay(20);
    }
}
