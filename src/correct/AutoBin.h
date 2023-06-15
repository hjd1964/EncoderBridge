// AutoBinning correct
#pragma once

#include "../Common.h"

// self calibrating routine to average out short term cyclic encoder interpolation errors of an RA axis encoder
// simply enable tracking within one minute of startup and leave the mount tracking undisturbed for 8 minutes
// AXIS1_ENCODER_SCALE provides artificial resolution to allow retarding or advancing the count to improve accuracy

// tracking errors during the time period specified will be used to quantify the average pulse arrival late/early

// number of ticks in the encoder interpolation window
#ifndef CORRECT_WINDOW
#define CORRECT_WINDOW        20  // 20x interpolation for my Gurley 8235S
#endif

#ifndef CORRECT_AVG_TICK
#define CORRECT_AVG_TICK  431.0F  // 431 milli-seconds per tick, on average, for a Gurley 8235S 200000 tick encoder
#endif

#ifndef AXIS1_ENCODER_SCALE
#define AXIS1_ENCODER_SCALE 1
#endif

#ifndef AXIS2_ENCODER_SCALE
#define AXIS2_ENCODER_SCALE 1
#endif

class AutoBin {
  public:
    int32_t apply(int32_t count);

  private:
    bool calibrate(int32_t count);
};
