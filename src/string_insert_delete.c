#include "methods.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

void string_insert_at(String self, const str in, const unsigned long pos) {
  long count = strlen(in);
  if (self->_->size < self->_->len + count + 1) {
    while (self->_->size < self->_->len + count + 1) {
      self->_->size += self->_->step;
      if (self->_->step_set == 0)
        self->_->step = (self->_->size < STEP_MAX) ? self->_->size : STEP_MAX;
    }
    {
      char cnt = 0;
      str option = NULL;
      while (cnt++ != 5 && option == NULL)
        option = realloc(self->_->text, self->_->size);
      if (option != NULL)
        self->_->text = option;
      else
        return;
    }
  }
  memmove(&self->_->text[pos + count], &self->_->text[pos],
          self->_->len - pos + 1);
  memcpy(&self->_->text[pos], in, count);
  self->_->len += count;
}
void string_delete_at(String self, const unsigned long pos,
                      unsigned long count) {
  if (pos > self->_->len)
    return;
  if (count >= self->_->len - pos)
    count = self->_->len - pos;
  memmove(&self->_->text[pos], &self->_->text[pos + count],
          self->_->len - pos - count + 1);
  self->_->len -= count;
  string_truncate_size(self);
}
