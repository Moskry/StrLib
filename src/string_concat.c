#include "methods.h"
#include "types.h"
#include <string.h>

String string_concat(String first, String second) {
  String final = new_string_reserve(first->_->len + second->_->len + 1, NULL);
  strcpy(final->_->text, first->_->text);
  strcat(final->_->text, second->_->text);
  first->free(first);
  second->free(second);

  final->_->len = final->_->size - 1;
  return final;
}
