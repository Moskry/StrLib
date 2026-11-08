#include "methods.h"
#include "types.h"

void string_set_step(const String self, int step) {
  self->_->step = step;
  self->_->step_set = 1;
}
