// Encoder Serial Bridge

// Firmware version ----------------------------------------------------------------------------------------------------------------
#define FirmwareName                "EncoderBridge"
#define FirmwareVersionMajor        1
#define FirmwareVersionMinor        0      // minor version 00 to 99
#define FirmwareVersionPatch        "b"    // for example major.minor patch: 10.03c

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
  #if DEBUG != OFF
    SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUD);
  #endif

  delay(2000);

  VLF("");
  VF("MSG: EncoderBridge, version "); V(FirmwareVersionMajor); V("."); V(FirmwareVersionMinor); VL(FirmwareVersionPatch);

  #if AXIS1_ENCODER != OFF
    encAxis1.init();
    encAxis1.setOrigin(AXIS1_ENCODER_ORIGIN);
  #endif

  #if AXIS2_ENCODER != OFF
    encAxis2.init();
    encAxis2.setOrigin(AXIS2_ENCODER_ORIGIN);
  #endif

  #if defined(ESP32)
    #if SERIAL_SWAP != ON
      SERIAL_ONSTEP.begin(SERIAL_BAUD, SERIAL_8N1, SERIAL_RX, SERIAL_TX);
    #else
      SERIAL_ONSTEP.begin(SERIAL_BAUD, SERIAL_8N1, SERIAL_SWAPPED_RX, SERIAL_SWAPPED_TX);
    #endif
  #else
    SERIAL_ONSTEP.begin(SERIAL_BAUD);
    #if defined(ESP8266) && SERIAL_SWAP == ON
      SERIAL_ONSTEP.swap();
    #endif
  #endif
}

void loop() {
  if (SERIAL_ONSTEP.available()) {
    char c = SERIAL_ONSTEP.read();
    #if AXIS1_ENCODER != OFF
      if (c == '1') {
        int32_t count = encAxis1.read();
        if (AXIS1_ENCODER_REVERSE == ON) count = -count;
        SERIAL_ONSTEP.print(count*AXIS1_ENCODER_SCALE);
        if (encAxis1.error) { SERIAL_ONSTEP.println("E"); encAxis1.error = false; } else
        if (encAxis1.warn) { SERIAL_ONSTEP.println("W"); encAxis1.warn = false; } else SERIAL_ONSTEP.println();
      } else
    #endif
    #if AXIS2_ENCODER != OFF
      if (c == '2') {
        int32_t count = encAxis2.read();
        if (AXIS2_ENCODER_REVERSE == ON) count = -count;
        SERIAL_ONSTEP.print(count*AXIS2_ENCODER_SCALE);
        if (encAxis2.error) { SERIAL_ONSTEP.println("E"); encAxis1.error = false; } else
        if (encAxis2.warn) { SERIAL_ONSTEP.println("W"); encAxis1.warn = false; } else SERIAL_ONSTEP.println();
      } else
    #endif
    {
      D("ERR: Unknown axis "); DL(c);
    }
  }
}
