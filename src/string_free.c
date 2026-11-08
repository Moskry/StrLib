#include "methods.h"
#include "types.h"
#include <stdlib.h>

void string_free(String self) {
  free(self->_->text);
  free(self->_);
  free(self);
}
