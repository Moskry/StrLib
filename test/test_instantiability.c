#include "StrLib.h"
#include <stdlib.h>
#include <string.h>

int main(void) {
  String name = new_string(NULL);
  String namer = new_string_reserve(50, NULL);
  if (name == NULL)
    return EXIT_FAILURE;
  else {
    namer->free(namer);
    name->free(name);
    return EXIT_SUCCESS;
  }
}
