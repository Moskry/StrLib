#include "methods.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

str string_slice(const struct string *self, const unsigned long start,
                 const unsigned long end) {
  if (start >= self->_->len)
    return NULL;
  long count = (((end > self->_->len) ? self->_->len  : end) - start);
  str slice = calloc(count + 1, sizeof(char));
  strncpy(slice, self->_->text + start, count);
  return slice;
}
