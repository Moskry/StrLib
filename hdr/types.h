#ifndef _TYPES_
#define _TYPES_

#include "StrLib.h"

#define STEP_MAX 256

struct _String {
  str text;
  long len;
  long size;
  int step;
  char step_set;
};

#endif
