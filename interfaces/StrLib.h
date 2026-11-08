#ifndef _STRLIB_
#define _STRLIB_

typedef char *str; // string slice / constants
// typedef struct _String *String;
typedef struct string {
  struct _String *_;
  // Assign a new value to an existing string
  int (*assign)(struct string *, str);
  // Assign a new value to an existing string, popping the old value
  str (*pop_assign)(struct string *, str);
  long (*length)(const struct string *);
  long (*size)(const struct string *);
  int (*clear)(struct string *);
  // Invalidates both Strings
  struct string *(*concat)(struct string *, struct string *);
  // Invalidates second String
  void (*append)(struct string *, struct string *);
  void (*append_copy)(struct string *, const struct string *const);
  void (*append_str)(struct string *, const str);
  str (*copy_to_str)(const struct string *const);
  // Invalidates String
  str (*to_str)(struct string *);
  // Cut off String at random value
  void (*truncate)(struct string *const, long);
  // Free unused memory
  void (*truncate_size)(struct string *);
  // Set ammount of bytes to allocate on each overflow. Default doubles every
  // time until maximum value allowed.
  void (*set_step)(struct string *const, int);
  str (*slice)(const struct string *, const unsigned long, const unsigned long);
  void (*insert_at)(struct string *, const str, const unsigned long);
  void (*delete_at)(struct string *, const unsigned long, unsigned long);
  void (*free)(struct string *);
} *String;

String new_string(const str text);
String new_string_reserve(const long size, const str text);
/*
String string_concat(String first, String second); // Invalidates both parent
strings void string_append(String self, String other); // Invalidates other void
string_append_copy(String self, const String other); void
string_append_str(String self, const str other);
str copy_to_str(String self);
str to_str(String self); // Invalidates string
void string_truncate(String self);
void string_set_step(
    int step); // Set ammount of bytes to allocate on each overflow. Default
               // doubles every time until 128
void string_free(String self);
*/

#endif
