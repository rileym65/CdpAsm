#include "header.h"

char* lookupDefine(char* l) {
  int i;
  for (i=0; i<defineCount; i++)
    if (strcmp(l,defines[i]) == 0) return defineValues[i];
  return NULL;
  }
