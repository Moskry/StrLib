#include "StrLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_assign(String a, const str to_assign) {
  a->assign(a, to_assign);
  str astr = a->copy_to_str(a);
  if (strcmp(astr, to_assign) == 0 && a->length(a) == strlen(to_assign)) {
    free(astr);
    return EXIT_SUCCESS;
  }
  free(astr);
  return EXIT_FAILURE;
}
static int test_pop_assign(String a, const str to_assign) {
  str oldstr = a->copy_to_str(a);
  str old = a->pop_assign(a, to_assign);
  str astr = a->copy_to_str(a);
  if (strcmp(astr, to_assign) == 0 && strcmp(oldstr, old) == 0 && a->length(a) == strlen(to_assign)) {
    free(astr);
    free(old);
    free(oldstr);
    return EXIT_SUCCESS;
  }
  free(astr);
  free(old);
  free(oldstr);
  return EXIT_FAILURE;
}


static int test_clear(String a) {
  a->clear(a);
  str astr = a->copy_to_str(a);
  if (strcmp(astr, "") == 0 && a->length(a) == 0) {
    free(astr);
    return EXIT_SUCCESS;
  }
  free(astr);
  return EXIT_FAILURE;
}

int main(void) {
  String a = new_string_reserve(50, "Bingo");
  if (test_assign(a, "Papyrus"))
    printf("test_assign passed!\n");
  if (test_clear(a))
    printf("test_clear passed!\n");
  a->assign(a, "Smile");
  if (test_pop_assign(a, "Whine"))
    printf("test_pop_assign passed!\n");
  a->free(a);
  return EXIT_SUCCESS;
}
