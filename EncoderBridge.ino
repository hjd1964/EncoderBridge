// Encoder Serial Bridge

#include "src/Common.h"

#include "src/lib/encoder/as37h39bb/As37h39bb.h"
#include "src/lib/encoder/cwCcw/CwCcw.h"
#include "src/lib/encoder/pulseDir/PulseDir.h"
#include "src/lib/encoder/quadrature/Quadrature.h"

#if AXIS1_ENCODER == AB
  Quadrature encAxis1(AXIS1_ENCODER_A_PIN, AXIS1_ENCODER_B_PIN, 1);
#elif AXIS1_ENCODER == CW_CCW
  CwCcw encAxis1(AXIS1_ENCODER_A_PIN, AXIS1_ENCODER_B_PIN, 1);
#elif AXIS1_ENCODER == PULSE_DIR
  PulseDir encAxis1(AXIS1_ENCODER_A_PIN, AXIS1_ENCODER_B_PIN, 1);
#elif AXIS1_ENCODER == AS37_H39B_B
  As37h39bb encAxis1(AXIS1_ENCODER_A_PIN, AXIS1_ENCODER_B_PIN, 1);
#elif AXIS1_ENCODER == SERIAL_BRIDGE
  SerialBridge encAxis1(1);
#endif

#if AXIS2_ENCODER == AB
  Quadrature encAxis2(AXIS2_ENCODER_A_PIN, AXIS2_ENCODER_B_PIN, 2);
#elif AXIS2_ENCODER == CW_CCW
  CwCcw encAxis2(AXIS2_ENCODER_A_PIN, AXIS2_ENCODER_B_PIN, 2);
#elif AXIS2_ENCODER == PULSE_DIR
  PulseDir encAxis2(AXIS2_ENCODER_A_PIN, AXIS2_ENCODER_B_PIN, 2);
#elif AXIS2_ENCODER == AS37_H39B_B
  As37h39bb encAxis2(AXIS2_ENCODER_A_PIN, AXIS2_ENCODER_B_PIN, 2);
#elif AXIS2_ENCODER == SERIAL_BRIDGE
  SerialBridge encAxis2(2);
#endif

void setup() {
  #if AXIS1_ENCODER != OFF
    encAxis1.init();
  #endif
  #if AXIS2_ENCODER != OFF
    encAxis2.init();
  #endif

  #if defined(ESP32)
    #if SERIAL_SWAP != ON
      SERIAL.begin(SERIAL_BAUD, SERIAL_8N1, SERIAL_RX, SERIAL_TX);
    #else
      SERIAL.begin(SERIAL_BAUD, SERIAL_8N1, SERIAL_SWAPPED_RX, SERIAL_SWAPPED_TX);
    #endif
  #else
    SERIAL.begin(SERIAL_BAUD);
    #if defined(ESP8266) && SERIAL_SWAP == ON
      SERIAL.swap();
    #endif
  #endif
}

void loop() {
  char c = Serial.read();
  #if AXIS1_ENCODER != OFF
    if (c == '1') {
      Serial.print((encAxis1.read() + AXIS1_ENCODER_OFFSET)*AXIS1_ENCODER_SCALE);
      if (encAxis1.error) Serial.println("E"); else
      if (encAxis1.warn) Serial.println("W"); else Serial.println();
    } else
  #endif
  #if AXIS2_ENCODER != OFF
    if (c == '2') {
      Serial.print((encAxis2.read() + AXIS2_ENCODER_OFFSET)*AXIS2_ENCODER_SCALE);
      if (encAxis2.error) Serial.println("E"); else
      if (encAxis2.warn) Serial.println("W"); else Serial.println();
    } else
  #endif
  {
    DL("ERR: Unknown axis")
  }
}
