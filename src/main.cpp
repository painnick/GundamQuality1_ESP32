#include <Arduino.h>
#include "esp_log.h"

#include "common.h"
#include "controllers/Mp3Controller.h"

#include "ESP32Servo.h"

#define MAIN_TAG "Main"

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

Servo neckServo;
Servo armServo;

#define NECK_ANGLE_START 90
#define NECK_ANGLE_LEFT 150
#define NECK_ANGLE_SHAKE1 30
#define NECK_ANGLE_SHAKE2 120
#define NECK_ANGLE_SHAKE3 135


#define ARM_ANGLE_START 0
#define ARM_ANGLE_1 16
#define ARM_ANGLE_2 20

#define ZAKU_MOTOR_RUN() (ledcWrite(CH_ZAKU_MOTOR, 255))
#define ZAKU_MOTOR_STOP() (ledcWrite(CH_ZAKU_MOTOR, 0))

#define GUNDAM_EYE_TURN_ON() (ledcWrite(CH_GUNDAM_EYE, 95))
#define GUNDAM_EYE_EMPHASIZE() (ledcWrite(CH_GUNDAM_EYE, 191))
#define GUNDAM_EYE_TURN_OFF() (ledcWrite(CH_GUNDAM_EYE, 0))

#define GUNDAM_GATLING_TURN_ON() (ledcWrite(CH_GUNDAM_GATLING, 127))
#define GUNDAM_GATLING_TURN_OFF() (ledcWrite(CH_GUNDAM_GATLING, 0))

#define ZAKU_EYE_TURN_ON() (ledcWrite(PIN_ZAKU_EYE, 127))
#define ZAKU_EYE_EMPHASIZE() (ledcWrite(PIN_ZAKU_EYE, 191))
#define ZAKU_EYE_TURN_OFF() (ledcWrite(PIN_ZAKU_EYE, 0))

void shakingHead();

void glance();

void runZakuMotor(int ms);

void setup()
{
    ESP_LOGI(MAIN_TAG, "Setup...");

    ESP_LOGI(MAIN_TAG, "Setup Neck Servo");
    pinMode(PIN_NECK_SERVO, OUTPUT);
    neckServo.attach(PIN_NECK_SERVO);
    neckServo.write(NECK_ANGLE_START);

    ESP_LOGI(MAIN_TAG, "Setup Arm Servo");
    pinMode(PIN_ARM_SERVO, OUTPUT);
    armServo.attach(PIN_ARM_SERVO);
    armServo.write(ARM_ANGLE_2);

    setupSound();
    delay(1000);

    playOpening();
    delay(4000);

    // Motor Driver
    ESP_LOGI(MAIN_TAG, "Setup Zaku Motor Driver");
    ledcSetup(CH_ZAKU_MOTOR, 1000, 8);
    ledcAttachPin(PIN_ZAKU_MOTOR, CH_ZAKU_MOTOR);

    // LEDs
    ESP_LOGI(MAIN_TAG, "Setup First Gundam Eyes");
    ledcSetup(CH_GUNDAM_EYE, 1000, 8);
    ledcAttachPin(PIN_GUNDAM_EYE, CH_GUNDAM_EYE);
    GUNDAM_EYE_TURN_OFF();

    ESP_LOGI(MAIN_TAG, "Setup First Gundam Gatling");
    ledcSetup(CH_GUNDAM_GATLING, 1000, 8);
    ledcAttachPin(PIN_GUNDAM_GATLING, CH_GUNDAM_GATLING);
    ledcWrite(CH_GUNDAM_GATLING, 0);

    ESP_LOGI(MAIN_TAG, "Setup Zaku Eyes");
    ledcSetup(CH_ZAKU_EYE, 1000, 8);
    ledcAttachPin(PIN_ZAKU_EYE, CH_ZAKU_EYE);
    ZAKU_EYE_TURN_OFF();
}

void loop()
{
    playGo();
    runZakuMotor(6000);

    GUNDAM_EYE_TURN_ON();
    delay(1000);

    ESP_LOGD(MAIN_TAG, "Arm Down #1");
    for (auto i = ARM_ANGLE_1; i >= ARM_ANGLE_START; i -= 3)
    {
        armServo.write(i);
        delay(100);
    }
    delay(1000);

    ESP_LOGD(MAIN_TAG, "Face Left");
    for (auto i = NECK_ANGLE_START; i <= NECK_ANGLE_LEFT; i += 5)
    {
        neckServo.write(i);
        delay(50);
    }
    delay(2000);

    GUNDAM_EYE_EMPHASIZE();
    playGatling();
    delay(500);
    for (auto i = 0; i < 5; i++)
    {
        GUNDAM_GATLING_TURN_ON();
        delay(100);
        GUNDAM_GATLING_TURN_OFF();
        delay(100);
    }
    stopGatling();

    GUNDAM_EYE_TURN_ON();
    delay(1000);

    ESP_LOGD(MAIN_TAG, "Face Front");
    for (auto i = NECK_ANGLE_LEFT; i >= NECK_ANGLE_START; i -= 5)
    {
        neckServo.write(i);
        delay(50);
    }
    delay(3000);

    ESP_LOGD(MAIN_TAG, "Face Left");
    for (auto i = NECK_ANGLE_START; i <= NECK_ANGLE_LEFT; i += 5)
    {
        neckServo.write(i);
        delay(50);
    }
    delay(1000);

    ESP_LOGD(MAIN_TAG, "Face Front");
    for (auto i = NECK_ANGLE_LEFT; i >= NECK_ANGLE_START; i -= 5)
    {
        neckServo.write(i);
        delay(50);
    }
    delay(1000);

    ESP_LOGD(MAIN_TAG, "Shake Head");
    shakingHead();
    delay(1000);

    runZakuMotor(3000);

    ESP_LOGD(MAIN_TAG, "Arm Up #1");
    for (auto i = ARM_ANGLE_START; i <= ARM_ANGLE_1; i += 3)
    {
        armServo.write(i);
        delay(100);
    }
    delay(3000);

    ESP_LOGD(MAIN_TAG, "Glance");
    glance();
    // delay(1000 * 1);

    runZakuMotor(2000);

    ESP_LOGD(MAIN_TAG, "Arm Up #2");
    for (auto i = ARM_ANGLE_1; i <= ARM_ANGLE_2; i += 3)
    {
        armServo.write(i);
        delay(100);
    }
    delay(1000);

    GUNDAM_EYE_TURN_OFF();

    delay(1000 * 10);
}

void shakingHead()
{
    for (auto i = NECK_ANGLE_START; i >= NECK_ANGLE_SHAKE1; i -= 5)
    {
        neckServo.write(i);
        delay(30);
    }

    for (auto i = NECK_ANGLE_SHAKE1; i <= NECK_ANGLE_SHAKE2; i += 5)
    {
        neckServo.write(i);
        delay(30);
    }

    for (auto i = NECK_ANGLE_SHAKE2; i >= NECK_ANGLE_START; i -= 5)
    {
        neckServo.write(i);
        delay(30);
    }
}

void glance()
{
    for (auto i = NECK_ANGLE_START; i <= NECK_ANGLE_SHAKE3; i += 3)
    {
        neckServo.write(i);
        delay(50);
    }

    delay(1000);

    for (auto i = NECK_ANGLE_SHAKE3; i >= NECK_ANGLE_START; i -= 3)
    {
        neckServo.write(i);
        delay(20);
    }
}

void runZakuMotor(const int ms)
{
    ZAKU_MOTOR_RUN();
    delay(ms);
    ZAKU_MOTOR_STOP();
}
