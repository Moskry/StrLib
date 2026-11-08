#include "StrLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_truncate_string_by_length(String s) {
  long old_size = s->size(s);
  str scpold = s->copy_to_str(s);
  s->truncate_size(s);
  str scp = s->copy_to_str(s);
  if (old_size >= s->size(s) && s->size(s) == s->length(s) + 1 &&
      strcmp(scpold, scp) == 0) {
    free(scpold);
    free(scp);
    return EXIT_SUCCESS;
  }
  printf("Expected size %ld, got %ld\n", s->length(s) + 1, s->size(s));
  free(scpold);
  free(scp);
  return EXIT_FAILURE;
}

static int test_truncate_string(String s, int value, const str expected) {
  s->truncate(s, value);
  str act = s->copy_to_str(s);
  if (s->size(s) == value + 1 && s->length(s) == value &&
      strcmp(expected, act) == 0) {
    free(act);
    return EXIT_SUCCESS;
  }
  printf("Expected %s, got %s\n", expected, act);
  free(act);
  return EXIT_FAILURE;
}

int main(void) {
  String a = new_string_reserve(50, "SOMETHING");
  if (!test_truncate_string_by_length(a))
    printf("test_truncate_string_by_length passed!\n");
  else {
    a->free(a);
    return EXIT_FAILURE;
  }
  if (!test_truncate_string(a, 5, "SOMET"))
    printf("test_truncate passed!\n");
  else {
    a->free(a);
    return EXIT_FAILURE;
  }
  a->free(a);
  return EXIT_SUCCESS;
}
