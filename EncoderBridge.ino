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
  #if DEBUG != OFF
    SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUD);
  #endif

  delay(2000);

  VLF("");
  VF("MSG: EncoderBridge, version "); V(FirmwareVersionMajor); V("."); V(FirmwareVersionMinor); VL(FirmwareVersionPatch);

  #if AXIS1_ENCODER != OFF
    encAxis1.init();
  #endif
  #if AXIS2_ENCODER != OFF
    encAxis2.init();
  #endif

  #ifdef AS37_SINGLE_TURN
    #if AXIS1_ENCODER == AS37_H39B_B || AXIS2_ENCODER == AS37_H39B_B
      VLF("--------------------------------------------------------------------------------");
      VLF("MSG: AS37_SINGLE_TURN mode detected >>> with the mount in the home position <<<");
      VLF("");
    #endif
    #if AXIS1_ENCODER == AS37_H39B_B
      VF("MSG: AXIS1_ENCODER_OFFSET in counts should be set to "); VL(uint32_t(4194304 - encAxis1.read()));
      encAxis1.setOrigin(AXIS1_ENCODER_OFFSET);
    #endif
    #if AXIS2_ENCODER == AS37_H39B_B
      VF("MSG: AXIS2_ENCODER_OFFSET in counts should be set to "); VL(uint32_t(4194304 - encAxis2.read()));
      encAxis2.setOrigin(AXIS2_ENCODER_OFFSET);
    #endif
    #if AXIS1_ENCODER == AS37_H39B_B
      encAxis1.offset = -4194304;
      VF("MSG: Axis1, counts at home should be 0 and currently are "); VL(encAxis1.read());
    #endif
    #if AXIS2_ENCODER == AS37_H39B_B
      encAxis2.offset = -4194304;
      VF("MSG: Axis2, counts at home should be 0 and currently are "); VL(encAxis2.read());
    #endif
    #if AXIS1_ENCODER == AS37_H39B_B || AXIS2_ENCODER == AS37_H39B_B
      VLF("--------------------------------------------------------------------------------");
    #endif
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
        if (encAxis1.error) SERIAL_ONSTEP.println("E"); else
        if (encAxis1.warn) SERIAL_ONSTEP.println("W"); else SERIAL_ONSTEP.println();
      } else
    #endif
    #if AXIS2_ENCODER != OFF
      if (c == '2') {
        int32_t count = encAxis2.read();
        if (AXIS2_ENCODER_REVERSE == ON) count = -count;
        SERIAL_ONSTEP.print(count*AXIS2_ENCODER_SCALE);
        if (encAxis2.error) SERIAL_ONSTEP.println("E"); else
        if (encAxis2.warn) SERIAL_ONSTEP.println("W"); else SERIAL_ONSTEP.println();
      } else
    #endif
    {
      D("ERR: Unknown axis "); DL(c);
    }
  }
}
