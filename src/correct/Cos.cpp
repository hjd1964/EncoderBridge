// Cos correct
// Only useful for absolute encoders

#include "Cos.h"

int32_t correct = 0;

int32_t Correct::apply(int32_t count) {
  // 200/20 = 10.0
  float phase = (count/(float)CORRECT_WINDOW - correct)/(float)CORRECT_WINDOW;
  phase = (phase - round(phase))*(CORRECT_PHASE/360.0F); // 0..1 represents the encoder interpolation sequence
  phase = phase * 2.0F * 3.14159F;                       // 0.0..6.28
  return count - cos(phase)*CORRECT_MAGNITUDE;
}
