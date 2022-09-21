// Cos correct
// Only useful for absolute encoders
#pragma once

// number of ticks in the encoder interpolation window
#ifndef CORRECT_WINDOW
#define CORRECT_WINDOW      20  // 20x interpolation for my Gurley 8235S
#endif

// scale of correction (depends on AXISn_ENC_SCALE)
#ifndef CORRECT_MAGNITUDE
#define CORRECT_MAGNITUDE   22  // for my Gurley 8235S
#endif

// phase of correction 
#ifndef CORRECT_PHASE
#define CORRECT_PHASE     0.0F  // offset of phase in degrees (+/- 360)
#endif

#include "../Common.h"

class Correct {
  public:
    int32_t apply(int32_t count);

  private:
};
