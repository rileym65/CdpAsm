#include "header.h"

void cleanup() {
  int i;
  for (i=0; i<numFiles; i++) free(files[i]);
  free(files);
  for (i=0; i<numSymbols; i++) {
    free(symbols[i]);
    free(symbolFile[i]);
    }
  free(symbols);
  free(symbolFile);
  free(symbolValues);
  }

