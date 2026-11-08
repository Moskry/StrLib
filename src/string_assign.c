#include "methods.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

int string_assign(String self, str value) {
  if (value == NULL)
    self->clear(self);

  long val_len = strlen(value);
  {
    char cnt = 0;
    str option = NULL;
    while (cnt++ != 5 && option == NULL) {
      option = realloc(self->_->text, val_len + 1);
    }
    if (option == NULL) return 1;
    self->_->text = option;
  }

  self->_->len = val_len;
  self->_->size = self->_->len + 1;
  self->_->step = self->_->step_set ? self->_->step : (self->_->size > STEP_MAX) ? STEP_MAX : self->_->size;
  strcpy(self->_->text, value);
  return 0;
}
