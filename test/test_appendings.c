#include "StrLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_concat(String a, String b, const char *expected) {

  String c = a->concat(a, b);
  str ctxt = c->copy_to_str(c);
  if (strcmp(ctxt, expected) == 0) {
    free(ctxt);
    c->free(c);
    return EXIT_SUCCESS;
  }
  free(ctxt);
  c->free(c);
  return EXIT_FAILURE;
}

static int test_append(String a, String b, const char *expected) {
  a->append(a, b);
  // b is now dangling
  str atxt = a->copy_to_str(a);
  if (strcmp(atxt, expected) == 0) {
    free(atxt);
    return EXIT_SUCCESS;
  }
  free(atxt);
  return EXIT_FAILURE;
}

static int test_append_copy(String a, String b, const char *expected_a,
                     const char *expected_b) {
  a->append_copy(a, b);
  b->append_copy(b, a);
  str astr = a->copy_to_str(a);
  str bstr = b->copy_to_str(b);

  if (strcmp(astr, expected_a) == 0 && strcmp(bstr, expected_b) == 0) {
    free(astr);
    free(bstr);
    return EXIT_SUCCESS;
  }
  free(astr);
  free(bstr);
  return EXIT_FAILURE;
}

static int test_append_str(String a, str b, const char *expected) {
  a->append_str(a, b);
  str astr = a->copy_to_str(a);
  if (strcmp(astr, expected) == 0) {
    free(astr);
    free(b);
    return EXIT_SUCCESS;
  }
  free(astr);
  free(b);
  return EXIT_FAILURE;
}

int main(void) {
  String a = new_string_reserve(50, "Hello");
  String b = new_string(" World!");

  int err = test_concat(a, b, "Hello World!");
  if (err) {
    printf("test_concat failed!");
    return err;
  }

  a = new_string_reserve(50, "Hello");
  b = new_string(" World!");

  err = test_append(a, b, "Hello World!");
  if (err) {
    printf("test_append failed!");
    return err;
  }
  a->assign(a, "Hello");
  b = new_string(" World!");

  err = test_append_copy(a, b, "Hello World!", " World!Hello World!");
  if (err) {
    printf("test_append_copy failed!");
    return err;
  }

  a->assign(a, "Hello");
  b->assign(b, " World!");
  str bstr = b->to_str(b);
  b = NULL;

  err = test_append_str(a, bstr, "Hello World!");
  if (err) {
    printf("test_append_str failed!");
    return err;
  }

  a->free(a);
  return EXIT_SUCCESS;
}
