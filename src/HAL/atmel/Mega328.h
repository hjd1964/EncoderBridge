// Platform setup ------------------------------------------------------------------------------------
#pragma once

// We define a more generic symbol, in case more Teensy boards based on different lines are supported
// __AVR__

// 1/100 second resolution
#define HAL_FRACTIONAL_SEC 100.0F

// This platform has 8 bit PWM
#ifndef HAL_VCC
  #define HAL_VCC 5.0F
#endif
#ifndef ANALOG_READ_RANGE
  #define ANALOG_READ_RANGE 1023 // always use 2^n - 1, within the platform's limits
#else
  #error "Configuration (Config.h): ANALOG_READ_RANGE can't be changed on this platform"
#endif
#ifndef ANALOG_WRITE_RANGE
  #define ANALOG_WRITE_RANGE 255 // always use 2^n - 1, within the platform's limits
#else
  #error "Configuration (Config.h): ANALOG_WRITE_RANGE can't be changed on this platform"
#endif

// This platform doesn't support true double precision math
#define HAL_NO_DOUBLE_PRECISION

// This is for ~16MHz AVR processors or similar.
#define HAL_SLOW_PROCESSOR

// Lower limit (fastest) step rate in us for this platform (in SQW mode) and width of step pulse
#define HAL_MAXRATE_LOWER_LIMIT 76.8
#define HAL_PULSE_WIDTH 10000 // in ns, estimated

// New symbol for the default I2C port -------------------------------------------------------------
#include <Wire.h>
#define HAL_WIRE Wire
#ifndef HAL_WIRE_CLOCK
  #define HAL_WIRE_CLOCK 20000
#endif

// Non-volatile storage ----------------------------------------------------------------------------
#if NV_DRIVER == NV_DEFAULT
  #undef NV_DRIVER
  #define NV_DRIVER NV_EEPROM
#endif

//--------------------------------------------------------------------------------------------------
// Internal MCU temperature (in degrees C)
#define HAL_TEMP() ( NAN )

//--------------------------------------------------------------------------------------------------
// General purpose initialize for HAL

#define HAL_INIT() { \
  analogReference(DEFAULT); \
}

//---------------------------------------------------------------------------------------------------
// Misc. includes to support this processor's operation

// stand-in for delayNanoseconds()
#define delayNanoseconds(ns) delayMicroseconds(ceilf(ns/1000.0F))
