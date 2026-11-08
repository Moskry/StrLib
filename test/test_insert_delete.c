#include "StrLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_insert(String self, int pos, const str to_ins, const str expected) {
  self->insert_at(self, to_ins, pos);
  str result = self->copy_to_str(self);
  if (strcmp(expected, result) == 0) {
    free(result);
    return EXIT_SUCCESS;
  }
    free(result);
    return EXIT_FAILURE;
}

int test_delete(String self, int pos, int len, const str expected) {
  self->delete_at(self, pos, len);
  str result = self->copy_to_str(self);
  if (strcmp(expected, result) == 0){
    free(result);
    return EXIT_SUCCESS;
  }
    free(result);
    return EXIT_FAILURE;
}

int main(void)
{
  String a = new_string("BIMBIM BAMBAM");
  int err = test_insert(a, 3, "BAM", "BIMBAMBIM BAMBAM");  
  if (err == EXIT_SUCCESS) printf("test_insert passed!\n"); 
  err = test_delete(a, 3, 3, "BIMBIM BAMBAM");
  if (err == EXIT_SUCCESS) printf("test_delete passed!\n");
  err = test_delete(a, 6, 50, "BIMBIM");
  if (err == EXIT_SUCCESS) printf("test_delete passed with overflow\n");
  a->free(a);
  return err;
}
