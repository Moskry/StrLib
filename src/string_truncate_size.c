#include "methods.h"
#include "types.h"
#include <stdlib.h>

void string_truncate_size(String self) {
  if (self->_->size != self->_->len + 1) {
    self->_->size = self->_->len + 1;
    if (self->_->step_set == 0 && self->_->step > self->_->size) {
      self->_->step = self->_->size;
    }
    char cnt = 0;
    str option;
    do
      option = realloc(self->_->text, self->_->size);
    while (cnt++ != 5 && option == NULL);
    if (option != NULL)
      self->_->text = option;
    else return;
  }
}
