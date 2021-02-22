#include "header.h"

void undef(char* l) {
  int i;
  int j;
  for (i=0; i<defineCount; i++) {
    if (strcmp(defines[i], l) == 0) {
      free(defineValues[i]);
      free(defines[i]);
      for (j=i; j<defineCount-1; j++) {
        defines[j] = defines[j+1];
        defineValues[j] = defineValues[j+1];
        }
      defineCount--;
      if (defineCount > 0) {
        defines = (char**)realloc(defines,sizeof(char*) * defineCount);
        defineValues = (char**)realloc(defineValues,sizeof(char*) * defineCount);
        }
      else {
        free(defines);
        free(defineValues);
        }
      }
    }
  }

