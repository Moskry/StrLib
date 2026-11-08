#include "methods.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

str copy_to_str(const struct string *const self) {
  char cnt = 0;
  str final = NULL;
  do
    final = malloc(sizeof(char) * self->_->len + 1);
  while (cnt++ != 5 && final == NULL);
  if (final != NULL)
    strcpy(final, self->_->text);
  return final;
}
