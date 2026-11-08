#include "methods.h"
#include "types.h"

long string_sizeof(const struct string *self) {
  return self->_->size;
}
