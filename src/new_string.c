#include "StrLib.h"
#include "methods.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

static void init_methods(String new) {
  new->clear = string_clear;
  new->pop_assign = string_pop_assign;
  new->assign = string_assign;
  new->length = string_length;
  new->size = string_sizeof;
  new->concat = string_concat;
  new->append = string_append;
  new->append_copy = string_append_copy;
  new->append_str = string_append_str;
  new->copy_to_str = copy_to_str;
  new->to_str = to_str;
  new->truncate = string_truncate;
  new->truncate_size = string_truncate_size;
  new->set_step = string_set_step;
  new->slice = string_slice;
  new->insert_at = string_insert_at;
  new->delete_at = string_delete_at;
  new->free = string_free;
}

String new_string(const str text) {
  String new;
  char cnt = 0;
  do
    new = malloc(sizeof(struct string));
  while (new == NULL && cnt++ != 5);
  if (new == NULL)
    return NULL;
  cnt = 0;
  do
    new->_ = malloc(sizeof(struct _String));
  while (new->_ == NULL && cnt++ != 5);
  if (new->_ == NULL) {
    free(new);
    return NULL;
  }
  cnt = 0;
  /*Should work but horribly inefficient. */
  /*
  new->_->len = text == (NULL ? 0) : strlen(text);
  new->_->size = text == (NULL ? 1) : new->_->len + 1;
  new->_->text =
      text == NULL ? malloc(sizeof(char)) : malloc(sizeof(char) * new->_->size);
  memset(new->_->text, 0, new->_->size);
  strcpy(new->_->text, text == NULL ? "" : text);
  new->_->step = (new->_->size < STEP_MAX) ? new->_->size : STEP_MAX;
  */
  if (text == NULL) {
    new->_->len = 0;
    new->_->size = 1;
    do
      new->_->text = calloc(1, sizeof(char));
    while (new->_->text == NULL && cnt++ != 5);
    if (new->_->text == NULL) {
      free(new->_);
      free(new);
      return NULL;
    }
    new->_->step = 1;
  } else {
    new->_->len = strlen(text);
    new->_->size = new->_->len + 1;
    do
      new->_->text = calloc(new->_->size, sizeof(char));
    while (new->_->text == NULL && cnt++ != 5);
    if (new->_->text == NULL) {
      free(new->_);
      free(new);
      return NULL;
    }
    strcpy(new->_->text, text);
    new->_->step = 1;
  }
  new->_->step_set = 0;

  init_methods(new);
  return new;
}
String new_string_reserve(const long size, const str text) {
  String new = new_string(text);

  if (new->_->size < size) {

    char cnt = 0;
    char *x;
    do
      x = realloc(new->_->text, size * sizeof(char));
    while (x == NULL && cnt++ != 5);
    if (x == NULL)
      exit(1);
    new->_->text = x;
    new->_->size = size;
  }
  return new;
}
