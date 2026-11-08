#include "methods.h"
#include "types.h"

str string_pop_assign(String self, str value) {
  str ret = self->copy_to_str(self);
  string_assign(self, value);
  return ret;
}
