// Platform setup ------------------------------------------------------------------------------------
#pragma once

// This is for fast processors with hardware FP
#define HAL_FAST_PROCESSOR

// Base rate for critical task timing (0.0095s = 0.14", 0.2 sec/day)
#define HAL_FRACTIONAL_SEC 105.2631579F

// Analog read and write
#ifndef HAL_VCC
  #define HAL_VCC 3.3F
#endif
#ifndef ANALOG_READ_RANGE
  #define ANALOG_READ_RANGE 1023 // always use 2^n - 1, within the platform's limits
#endif
#ifndef ANALOG_WRITE_RANGE
  #define ANALOG_WRITE_RANGE 255 // always use 2^n - 1, within the platform's limits
#endif

// Lower limit (fastest) step rate in us for this platform (in SQW mode) and width of step pulse
#define HAL_MAXRATE_LOWER_LIMIT 40
#define HAL_PULSE_WIDTH 200 // in ns, measured 1/18/22 (ESP32 v2.0.0)

// New symbol for the default I2C port -------------------------------------------------------------
#include <Wire.h>
#define HAL_WIRE Wire
#ifndef HAL_WIRE_CLOCK
  #define HAL_WIRE_CLOCK 100000
#endif
#if (defined(I2C_SCL_PIN) && I2C_SCL_PIN != OFF) && (defined(I2C_SDA_PIN) && I2C_SDA_PIN != OFF)
  #define WIRE_BEGIN() HAL_WIRE.begin(I2C_SDA_PIN, I2C_SCL_PIN); HAL_WIRE.setClock(HAL_WIRE_CLOCK);
#else
  #define WIRE_BEGIN() HAL_WIRE.begin(); HAL_WIRE.setClock(HAL_WIRE_CLOCK);
#endif

// Non-volatile storage ----------------------------------------------------------------------------
#if NV_DRIVER == NV_DEFAULT
  #undef NV_DRIVER
  #define NV_DRIVER NV_ESP
#endif

//--------------------------------------------------------------------------------------------------
// Internal MCU temperature (in degrees C)
// Correction for ESP32's internal temperture sensor
#ifndef INTERNAL_TEMP_CORRECTION
  #define INTERNAL_TEMP_CORRECTION 0
#endif
#define HAL_TEMP() ( temperatureRead() + INTERNAL_TEMP_CORRECTION )

//--------------------------------------------------------------------------------------------------
// General purpose initialize for HAL, optionally also early init of SERIAL_SIP/PIP or SERIAL_BT

#if SERIAL_BT_MODE == SLAVE
  #include <BluetoothSerial.h>
  extern BluetoothSerial bluetoothSerial;
  #define SERIAL_BT bluetoothSerial
#endif
#if defined(SERIAL_BT)
  #define SERIAL_BT_BEGIN() SERIAL_BT.begin(SERIAL_BT_NAME);
#else
  #define SERIAL_BT_BEGIN()
#endif

#if (defined(SERIAL_BT_MODE) && SERIAL_BT_MODE != OFF) && (defined(SERIAL_IP_MODE) && SERIAL_IP_MODE != OFF)
  #error "Configuration (Config.h): SERIAL_BT_MODE and SERIAL_IP_MODE can't be enabled at the same time, disable one or both options."
#endif

#ifdef SERVO_ANALOG_WRITE_FREQUENCY
  #define HAL_INIT() { \
    analogReadResolution((int)log2(ANALOG_READ_RANGE + 1)); \
    analogWriteResolution((int)log2(ANALOG_WRITE_RANGE + 1)); \
    analogWriteFrequency(SERVO_ANALOG_WRITE_FREQUENCY); \
    SERIAL_BT_BEGIN(); \
    WIRE_BEGIN(); \
  }
#else
  #define HAL_INIT() { \
    analogReadResolution((int)log2(ANALOG_READ_RANGE + 1)); \
    analogWriteResolution((int)log2(ANALOG_WRITE_RANGE + 1)); \
    SERIAL_BT_BEGIN(); \
    WIRE_BEGIN(); \
  }
#endif

//---------------------------------------------------------------------------------------------------
// Misc. includes to support this processor's operation

// MCU reset
#define HAL_RESET() ESP.restart()

// a really short fixed delay (none needed)
#define HAL_DELAY_25NS()

#ifdef ARDUINO_ESP32C3_DEV
  // stand-in for delayNanoseconds(), assumes 80MHz clock
  #define delayNanoseconds(ns) { unsigned int c = ESP.getCycleCount() + ns/12.5F; do {} while ((int)(ESP.getCycleCount() - c) < 0); }
#else
  // stand-in for delayNanoseconds(), assumes 240MHz clock
  #include "xtensa/core-macros.h"
  #define delayNanoseconds(ns) { unsigned int c = xthal_get_ccount() + ns/4.166F; do {} while ((int)(xthal_get_ccount() - c) < 0); }
#endif
