#include "header.h"

void opcode(char* o, char* a, char* t) {
  int n;
  int i;
  for (i=0; i<numOpcodes; i++) {
    if (strcasecmp(o,o_opcodes[i]) == 0 &&
        strcasecmp(a,o_args[i]) == 0) {
      strcpy(o_trans[i], t);
      return;
      }
    }
  strcpy(o_opcodes[numOpcodes], o);
  strcpy(o_args[numOpcodes], a);
  strcpy(o_trans[numOpcodes], t);
  n = 0;
  if (a[0] != 0) {
    n = 1;
    for (i=0; i<strlen(a); i++)
      if (a[i] == ',') n++;
    }
  o_argCount[numOpcodes] = n;
  numOpcodes++;
  }
