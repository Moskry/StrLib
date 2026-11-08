#include "methods.h"
#include "types.h"

long string_length(const struct string *self) {
  return self->_->len;
}
