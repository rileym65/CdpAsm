#include "header.h"

int lookupOpcode() {
  int i;
  int j;
  int valid;
  i = 0;
  for (i=0; i<numOpcodes; i++) {
    if (strcasecmp(op,o_opcodes[i]) == 0) {
      if (o_args[i][0] == 'M' && argCount > 0) return i;
      if (argCount == o_argCount[i]) {
        if (argCount == 0) return i;
        valid = -1;
        for (j=0; j<o_argCount[i]; j++) {
          if (o_args[i][j*2] == 'L' && strlen(argsAscii[j]) == 0) valid = 0;
          if (o_args[i][j*2] == 'N' && (args[j] & 0xffff) > 15) valid = 0;
          if (o_args[i][j*2] == 'R' && (((args[j] & FLG_R) == 0) || ((args[j] & 0xffff) > 15))) valid = 0;
          if (o_args[i][j*2] == 'B' && (args[j] & 0xffff) > 255) valid = 0;
          if (o_args[i][j*2] == 'P') {
            if (pass == 2)
              if ((args[j] & 0xff00) != (address & 0xff00)) showError("Error: Out of page branch");
            }
          }
        if (valid) return i;
        }
      }
    }
  return -1;
  }
