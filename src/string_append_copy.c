#include "methods.h"
#include <stdlib.h>

void string_append_copy(String self, const struct string *const other) {
  str parsed = copy_to_str(other);

  string_append_str(self, parsed);

  free(parsed);
}
