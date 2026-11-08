#include "methods.h"

void string_append(String self, String other) {
  string_append_copy(self, other);
  other->free(other);
}
