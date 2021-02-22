#include "header.h"

int lookupLabel(char* l) {
  int i;
  for (i=0; i<labelCount; i++)
    if (strcmp(l,labels[i]) == 0) return labelValues[i];
  return -1;
  }
