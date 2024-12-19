// Platform setup ------------------------------------------------------------------------------------
#pragma once

// We define a more generic symbol, in case more STM32 boards based on different lines are supported
#define __ARM_STM32__

// Base rate for critical task timing (0.0038s = 0.06", 0.2 sec/day)
#define HAL_FRACTIONAL_SEC 263.1578947F

// Analog read and write
#ifndef HAL_VCC
  #define HAL_VCC 3.3F
#endif
#ifndef ANALOG_READ_RANGE
  #define ANALOG_READ_RANGE 1023
#else
  #error "Configuration (Config.h): ANALOG_READ_RANGE can't be changed on this platform"
#endif
#ifndef ANALOG_WRITE_RANGE
  #define ANALOG_WRITE_RANGE 255
#endif

// Lower limit (fastest) step rate in uS for this platform (in SQW mode) and width of step pulse
#define HAL_FAST_PROCESSOR
#define HAL_MAXRATE_LOWER_LIMIT 14   // assumes optimization set to Fastest (-O3)
#define HAL_PULSE_WIDTH 250          // in ns, estimated

#include <HardwareTimer.h>

// Interrupts
#define cli() noInterrupts()
#define sei() interrupts()

// New symbol for the default I2C port ---------------------------------------------------------------
#include <Wire.h>
#define HAL_WIRE Wire
#ifndef HAL_WIRE_CLOCK
  #define HAL_WIRE_CLOCK 100000
#endif

// Non-volatile storage ------------------------------------------------------------------------------
#undef E2END
#if NV_DRIVER == NV_DEFAULT
  #undef NV_DRIVER
  #if PINMAP == FYSETC_S6_2
    // The FYSETC S6 v2 has a 4096 byte EEPROM built-in
    #define NV_DRIVER NV_2432
  #elif PINMAP == FYSETC_S6
    // The FYSETC S6 has a 2048 byte EEPROM built-in
    #define NV_DRIVER NV_2416
  #else
    // Fallback to the EEPROM present on an ZS-042 module
    #define NV_DRIVER NV_AT24C32
  #endif
#endif

//--------------------------------------------------------------------------------------------------
// Internal MCU temperature (in degrees C)
#define HAL_TEMP() ( NAN )

//--------------------------------------------------------------------------------------------------
// General purpose initialize for HAL
#define HAL_INIT() { \
  analogWriteResolution((int)log2(ANALOG_WRITE_RANGE + 1)); \
}

//---------------------------------------------------------------------------------------------------
// Misc. includes to support this processor's operation

// MCU reset
#define HAL_RESET() NVIC_SystemReset()

// a really short fixed delay (none needed)
#define HAL_DELAY_25NS()

// stand-in for delayNanoseconds()
#define delayNanoseconds(ns) delayMicroseconds(ceilf(ns/1000.0F))
