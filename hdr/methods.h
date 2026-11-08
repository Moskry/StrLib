#ifndef _METHODS_
#define _METHODS_

#include "StrLib.h"

String string_concat(String first, String second);
int string_assign(String self, str value);
str string_pop_assign(String self, str value);
long string_length(const struct string *self);
long string_sizeof(const struct string *self);
int string_clear(String self);
void string_append(String self, String other);
void string_append_copy(String self, const struct string *const other);
void string_append_str(String self, const str other);
str copy_to_str(const struct string *const self);
str to_str(String self);
void string_truncate(const String self, long num);
void string_truncate_size(String self);
void string_set_step(const String self, int step);
void string_free(String self);
str string_slice(const struct string *self, const unsigned long start, const unsigned long end);
void string_insert_at(String self, const str in, const unsigned long pos);
void string_delete_at(String self, const unsigned long pos,
                      unsigned long count);

#endif
