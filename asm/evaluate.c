#include "header.h"

UInt32 evaluate(char* line) {
//  int i;
  tokenize(line);
//for (i=0; i<numTokens; i++)
//  printf("  %08x\n",tokens[i]);
//printf("-----\n");
  reduce(0,numTokens-1);
//for (i=0; i<numTokens; i++)
//  printf("  %08x\n",tokens[i]);
  if (numTokens == 0) return 0;
  if (numTokens == 1) return tokens[0];
  printf("Expression error: (%d) %s\n",numTokens,line);
  return 0;
  }
