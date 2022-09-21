// -------------------------------------------------------------------------------------------------
// Pin map for ESP32S2
#pragma once

// locate WeMos D1 R32 serial port pins to match WeMos D1 Mini main and swapped port pins
#ifndef SERIAL_RX
  #define SERIAL_RX         11
#endif
#ifndef SERIAL_TX
  #define SERIAL_TX         12
#endif
#ifndef SERIAL_SWAPPED_RX
  #define SERIAL_SWAPPED_RX 12
#endif
#ifndef SERIAL_SWAPPED_TX
  #define SERIAL_SWAPPED_TX 11
#endif

#define AXIS1_ENCODER_A_PIN     7   // pin# for Axis1 encoder, for A or CW  or MA/CLK
#define AXIS1_ENCODER_B_PIN     9   // pin# for Axis1 encoder, for B or CCW or SLO
#define AXIS2_ENCODER_A_PIN     35  // pin# for Axis1 encoder, for A or CW  or MA/CLK
#define AXIS2_ENCODER_B_PIN     33  // pin# for Axis1 encoder, for B or CCW or SLO
