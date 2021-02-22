#include "header.h"

int findLabel(char* l) {
  int i;
  for (i=0; i<labelCount; i++)
    if (strcmp(l,labels[i]) == 0) return i;
  return -1;
  }
