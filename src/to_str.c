#include "methods.h"
#include "types.h"
#include <stdlib.h>

str to_str(String self) {
  if (self == NULL || self->_ == NULL || self->_->text == NULL)
    return NULL;
  str final = self->_->text;
  free(self->_);
  free(self);
  return final;
}
