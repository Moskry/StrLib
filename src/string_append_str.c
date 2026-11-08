#include "methods.h"
#include "types.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void string_append_str(String self, const str other) {
  size_t strsize = strlen(other);
  self->_->len += strsize;
  while (self->_->size < self->_->len + 1) {
    self->_->size += self->_->step;
    if (self->_->step_set == 0)
      self->_->step = self->_->size < STEP_MAX ? self->_->size : STEP_MAX;
  }
  {
    char cnt = 0;
    str option;
    do
      option = realloc(self->_->text, sizeof(char) * self->_->size);
    while (cnt++ != 5 && option == NULL);
    if (option == NULL)
      exit(1);
    self->_->text = option;
  }
  strcat(self->_->text, other);
}
