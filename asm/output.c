#include "header.h"

void output(byte b) {
  codes[numCodes++] = b;
  if (pass == 2 && memory[address] != 0) {
    sprintf(tmp,"Address multiply defined: %04x",address);
    showError(tmp);
    }
  codeGenerated++;
  memory[address] = 1;
  if (address > highest) highest = address;
  if (address < lowest) lowest = address;
  if (pass == 2) {
    if (outCount == 0) fprintf(outFile,":%04x",address);
    fprintf(outFile," %02x",b);
    outCount++;
    if (outCount == 16) flush();
    }
  address++;
  }
