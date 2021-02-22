#include "header.h"

int assemblyPass(int p) {
  int i;
  for (i=0; i<65536; i++) memory[i] = 0;
  pass = p;
  address = 0;
  linesRead = 0;
  lineNumber = 0;
  codeGenerated = 0;
  lowest = 0xffff;
  highest = 0;
  lineNumberSP = 0;
  while (readLine()) {
    if (strlen(line) > 0) assemble(line);
      else if (pass == 2 && showList) {
        if (lineNumberSP == 0) printf("[%05d]                   %s\n",lineNumber,rawLine);
          else printf("<%05d>                   %s\n",lineNumber,rawLine);
        }
    }
  return 0;
  }
