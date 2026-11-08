#include "StrLib.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static int test_copy_to_str(String string) {
  str test = string->copy_to_str(string);
  str test1 = string->copy_to_str(string);
  if (strcmp(test, test1) == 0 && strcmp(test, "Dragan") == 0) {
    free(test);
    free(test1);
    return EXIT_SUCCESS;
  }
  free(test);
  free(test1);
  return EXIT_FAILURE;
}

static int test_to_str(String string) {
  str test = string->to_str(string);
  if (strcmp(test, "Dragan") == 0) {
    free(test);
    return EXIT_SUCCESS;
  } else {
    free(test);
    return EXIT_FAILURE;
  }
}

int main(void) {
  String name = new_string("Dragan");
  int ret = test_copy_to_str(name);
  ret = test_to_str(name);
  return ret;
}
