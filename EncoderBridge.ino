// Encoder Serial Bridge

// Firmware version ----------------------------------------------------------------------------------------------------------------
#define FirmwareName                "EncoderBridge"
#define FirmwareVersionMajor        1
#define FirmwareVersionMinor        1      // minor version 00 to 99
#define FirmwareVersionPatch        "a"    // for example major.minor patch: 10.03c

#include "src/Common.h"
NVS nv;

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

#define EncoderSettingsSize 72
typedef struct EncoderAxis {
  uint32_t zero;
  uint32_t offset;
  int32_t diffTo;
  double ticksPerDeg;
  int16_t reverse;
} EncoderAxis;

typedef struct EncoderSettings {
    bool autoSync;
    EncoderAxis axis1;
    EncoderAxis axis2;
} EncoderSettings;

EncoderSettings settings = {
  false,
  {AXIS1_ENCODER_ORIGIN, 0, 0, 0, AXIS1_ENCODER_REVERSE},
  {AXIS2_ENCODER_ORIGIN, 0, 0, 0, AXIS2_ENCODER_REVERSE}
};

void setup() {
  #if DEBUG != OFF
    SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUD);
  #endif

  delay(2000);

  VLF("");
  VF("MSG: EncoderBridge, version "); V(FirmwareVersionMajor); V("."); V(FirmwareVersionMinor); VL(FirmwareVersionPatch);

  // start low level hardware
  VLF("MSG: Setup, HAL initalize");
  HAL_INIT();
  HAL_NV_INIT();

  nv.ignoreCache(true);

  // get NV ready
  if (!nv.isKeyValid(INIT_NV_KEY)) {
    VF("MSG: NV, invalid key wipe "); V(nv.size); VLF(" bytes");
    if (nv.verify()) { VLF("MSG: NV, ready for reset to defaults"); }
  } else { VLF("MSG: NV, correct key found"); }

  // confirm the data structure size
  if (EncoderSettingsSize < sizeof(EncoderSettings)) { nv.initError = true; DL("ERR: Setup, EncoderSettingsSize error NV subsystem writes disabled"); }

  // write the default settings to NV
  if (!nv.hasValidKey()) {
    VLF("MSG: Setup, writing defaults to NV");
    nv.writeBytes(NV_ENCODER_SETTINGS_BASE, &settings, sizeof(EncoderSettings));
    nv.wait();
  }

  // read the settings
  nv.readBytes(NV_ENCODER_SETTINGS_BASE, &settings, sizeof(EncoderSettings));

  // init is done, write the NV key if necessary
  if (!nv.hasValidKey()) {
    nv.writeKey((uint32_t)INIT_NV_KEY);
    nv.wait();
    if (!nv.isKeyValid(INIT_NV_KEY)) { DLF("ERR: NV, failed to read back key!"); } else { VLF("MSG: NV, reset complete"); }
  }

  #if AXIS1_ENCODER != OFF
    VF("MSG: Absolute Encoder Axis1"); VF(", AXIS1_ENCODER_OFFSET "); V(uint32_t(settings.axis1.zero)); VLF(" read from NV/EEPROM");
    encAxis1.init();
    encAxis1.setOrigin(settings.axis1.zero);
  #endif

  #if AXIS2_ENCODER != OFF
    VF("MSG: Absolute Encoder Axis2"); VF(", AXIS2_ENCODER_OFFSET "); V(uint32_t(settings.axis2.zero)); VLF(" read from NV/EEPROM");
    encAxis2.init();
    encAxis2.setOrigin(settings.axis2.zero);
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
  static char c3 = -1;
  static char c2 = -1;
  static char c1 = -1;
  static char c = -1;

  if (SERIAL_ONSTEP.available()) {
    c3 = c2;
    c2 = c1;
    c1 = c;
    c = SERIAL_ONSTEP.read();

    #if AXIS1_ENCODER != OFF
      if (c == '1') {
        int32_t count = encAxis1.read();
        if (AXIS1_ENCODER_REVERSE == ON) count = -count;
        SERIAL_ONSTEP.print(count);
        if (encAxis1.error) { SERIAL_ONSTEP.println("E"); encAxis1.error = false; } else
        if (encAxis1.warn) { SERIAL_ONSTEP.println("W"); encAxis1.warn = false; } else SERIAL_ONSTEP.println();
      }
    #endif

    #if AXIS2_ENCODER != OFF
      if (c == '2') {
        int32_t count = encAxis2.read();
        if (AXIS2_ENCODER_REVERSE == ON) count = -count;
        SERIAL_ONSTEP.print(count);
        if (encAxis2.error) { SERIAL_ONSTEP.println("E"); encAxis1.error = false; } else
        if (encAxis2.warn) { SERIAL_ONSTEP.println("W"); encAxis1.warn = false; } else SERIAL_ONSTEP.println();
      } else
    #endif

    if (c3 == ':' && c2 == 'S' && c1 == 'O' && c == '#') {
      #if AXIS1_ENCODER != OFF
        encAxis1.origin = 0;
        encAxis1.offset = 0;
        settings.axis1.zero = (uint32_t)(-encAxis1.read());
        encAxis1.origin = settings.axis1.zero;
        VF("MSG: Absolute Encoder Axis1"); VF(", saving AXIS1_ENCODER_OFFSET "); V(uint32_t(settings.axis1.zero)); VLF(" to NV/EEPROM");
      #endif

      #if AXIS2_ENCODER != OFF
        encAxis2.origin = 0;
        encAxis2.offset = 0;
        settings.axis2.zero = (uint32_t)(-encAxis2.read());
        encAxis2.origin = settings.axis2.zero;
        VF("MSG: Absolute Encoder Axis2"); VF(", saving AXIS2_ENCODER_OFFSET "); V(uint32_t(settings.axis2.zero)); VLF(" to NV/EEPROM");
      #endif

      nv.updateBytes(NV_ENCODER_SETTINGS_BASE, &settings, sizeof(EncoderSettings));
      nv.wait();
    }

  }
}
