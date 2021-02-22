#include "header.h"

void flush() {
  if (outCount > 0) fprintf(outFile,"\n");
  outCount = 0;
  }
