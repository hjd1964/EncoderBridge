// Broadcom AS37-H39B-B BISS-C encoders
#pragma once

#include "../Encoder.h"

#if AXIS1_ENCODER == BISS || AXIS2_ENCODER == BISS || AXIS3_ENCODER == BISS || \
    AXIS4_ENCODER == BISS || AXIS5_ENCODER == BISS || AXIS6_ENCODER == BISS || \
    AXIS7_ENCODER == BISS || AXIS8_ENCODER == BISS || AXIS9_ENCODER == BISS

  // designed according protocol description found in as38-H39e-b-an100.pdf

  // similar broadcom devices have range of 10MHz to 80 KHz
  #ifndef AS37_CLOCK_RATE_KHZ
    #define AS37_CLOCK_RATE_KHZ 250
  #endif

  class Biss : public Encoder {
    public:
      // initialize BISS encoder
      // nvAddress holds settings for the 9 supported axes, 9*4 = 72 bytes; set nvAddress 0 to disable
      Biss(int16_t maPin, int16_t sloPin, int16_t axis);

      // get device ready for use
      void init();

      // set encoder origin
      void setOrigin(uint32_t count);

      // read encoder count
      int32_t read();

      // write encoder position
      void write(int32_t count);

    private:
      // read encoder position with error recovery
      bool readEncLatest(uint32_t &position);

      // read encoder position
      bool readEnc(uint32_t &position);

      uint32_t good = 0;
      uint32_t bad = 0;
      int16_t axis;
      uint16_t nvAddress;

      int16_t clkPin;
      int16_t sloPin;

      uint32_t lastValidTime = 0;
      uint32_t lastValidPosition = 0;
  };

#endif
