// SWS Bridge encoder
#pragma once

#include "../Encoder.h"

#if AXIS1_ENCODER == SWS_BRIDGE && AXIS2_ENCODER == SWS_BRIDGE

class SwsBridge : public Encoder {
  public:
    SwsBridge(int16_t axis);

    // get current position
    int32_t read();

    // set current position to value
    void write(int32_t count);

    // get count
    int32_t get();

    // set count to value
    void set(int32_t count);

  private:
    char channel[2] = "0";
    int axis = 0;
};

#endif
