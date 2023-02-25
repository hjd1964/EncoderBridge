// AutoBin correct

#include "AutoBin.h"

float pulse_frac_average[CORRECT_WINDOW];
uint32_t lastCount;
unsigned long lastTime;

int32_t AutoBin::apply(int32_t count) {
  if (calibrate(count/AXIS1_ENCODER_SCALE)) return count;

  return count + round(pulse_frac_average[(count/AXIS1_ENCODER_SCALE)%AXIS1_ENCODER_SCALE]);
}

// get the average in the first eight minutes of operation during which time the mount should be tracking normally
bool AutoBin::calibrate(int32_t count) {
  if (lastCount != count && millis() < 4800000) {
    unsigned long thisTime = millis();

    long pulse_time = (long)(thisTime - lastTime);                               // should be 431
    float pulse_frac = ((pulse_time/CORRECT_AVG_TICK)-1.0F)*AXIS1_ENCODER_SCALE; // should be 0
    pulse_frac_average[count%20] = (pulse_frac_average[count%CORRECT_WINDOW]*9.0F + pulse_frac)/10.0F;

    lastTime = thisTime;
    lastCount = count;
    return false;
  }
  return true;
}
