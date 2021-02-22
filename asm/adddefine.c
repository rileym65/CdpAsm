#include "header.h"

void addDefine(char* l,char* v) {
  int i;
  if (pass == 2) return;
  for (i=0; i<defineCount; i++) {
    if (strcmp(defines[i], l) == 0) {
      showError("Symbol already defined");
      return;
      }
    }
  if (defineCount == 0) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (char**)malloc(sizeof(char*));
    }
  else {
    defines = (char**)realloc(defines,sizeof(char*) * (defineCount+1));
    defineValues = (char**)realloc(defineValues,sizeof(char*) * (defineCount+1));
    }
  defines[defineCount] = (char*)malloc(strlen(l) + 1);
  defineValues[defineCount] = (char*)malloc(strlen(v) + 1);
  strcpy(defines[defineCount], l);
  strcpy(defineValues[defineCount], v);
  defineCount++;
  }

