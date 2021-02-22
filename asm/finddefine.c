#include "header.h"

int findDefine(char* l) {
  int i;
  for (i=0; i<defineCount; i++)
    if (strcmp(l,defines[i]) == 0) return i;
  return -1;
  }
