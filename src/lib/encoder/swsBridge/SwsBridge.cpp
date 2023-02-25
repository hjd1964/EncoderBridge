// SWS Bridge encoder

#include "SwsBridge.h"

#if AXIS1_ENCODER == SWS_BRIDGE && AXIS2_ENCODER == SWS_BRIDGE

SwsBridge::SwsBridge(int16_t axis) {
  if (axis < 1 || axis > 2) return;
  count = 0;
  offset = 0;
  initialized = true;
  ready = false;
  this->axis = axis;
}

int32_t SwsBridge::read() {
  if (!initialized) return 0;
  return count + offset;
}

void SwsBridge::write(int32_t count) {
  if (!initialized) return;
  offset = count - this->count;
}

int32_t SwsBridge::get() {
  if (!initialized) return 0;
  return count;
}

void SwsBridge::set(int32_t count) {
  if (!initialized) return;
  this->count = count;
  ready = true;
}

#endif
