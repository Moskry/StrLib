#include "methods.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

int string_clear(String self) {
  {
    char cnt = 0;
    str option = NULL;
    do
      option = realloc(self->_->text, 1);
    while (option == NULL && cnt++ != 5);
    if (option != NULL)
      self->_->text = option;
    else return 1;
  }
  self->_->text[0] = 0;
  self->_->len = 0;
  self->_->size = 1;
  self->_->step = self->_->step_set ? self->_->step : self->_->size;
  return 0;
}
