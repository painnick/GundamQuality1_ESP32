#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 33 // dfplayer(FIXED)
#define PIN_MP3_RX 32 // dfplayer(FIXED)

#define PIN_NECK_SERVO 27
#define PIN_ARM_SERVO 26

#define PIN_ZAKU_MOTOR 25
#define CH_ZAKU_MOTOR 1

#define PIN_GUNDAM_EYE 15
#define CH_GUNDAM_EYE 2

#define PIN_GUNDAM_GATLING 4
#define CH_GUNDAM_GATLING 3

#define PIN_ZAKU_EYE 18
#define CH_ZAKU_EYE 4
