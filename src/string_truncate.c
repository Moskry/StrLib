#include "methods.h"
#include "types.h"
#include <stdlib.h>

void string_truncate(const String self, long num) {
  if (self->_->size != num + 1) {
    char cnt = 0;
    str temp;

    char end = self->_->text[num];
    self->_->text[num] = 0;

    do
      temp = realloc(self->_->text, sizeof(char) * (num + 1));
    while (cnt++ != 5 && temp == NULL);
    if (temp == NULL) {
      self->_->text[num] = end;
      return;
    }
    self->_->text = temp;
  }

  self->_->size = num + 1;
  if (self->_->len > num)
    self->_->len = num;
  if (self->_->step > num + 1)
    self->_->step = num + 1;
}
