#include "StrLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  String a = new_string("SOMETHING");
  str slicea = a->slice(a, 4, 20);
  str sliceb = a->slice(a, 2, 4);
  if (strcmp(slicea, "THING") == 0 && strcmp(sliceb, "ME") == 0) {
    free(slicea);
    free(sliceb);
    free(a);
    return EXIT_SUCCESS;
  }
  printf("Error\nexpected: THING, got: %s\nexpected: ME, got: %s\n", slicea, sliceb);
  free(slicea);
  free(sliceb);
  free(a);
  return EXIT_FAILURE;
}
