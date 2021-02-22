#include "header.h"

int addSymbol(char* symbol, word value, char* file) {
  int i;
  for (i=0; i<numSymbols; i++) {
    if (strcmp(symbols[i], symbol) == 0) {
      if (symbolValues[i] == value) return -1;
      printf("Error: Symbol '%s' redefined.  Original file: %s\n",
             symbol, symbolFile[i]);
      return 0;
      }
    }
  if (numSymbols == 0) {
    symbols = (char**)malloc(sizeof(char*));
    symbolFile = (char**)malloc(sizeof(char*));
    symbolValues = (word*)malloc(sizeof(word));
    }
  else {
    symbols = (char**)realloc(symbols,sizeof(char*)*(numSymbols+1));
    symbolFile = (char**)realloc(symbolFile,sizeof(char*)*(numSymbols+1));
    symbolValues = (word*)realloc(symbolValues,sizeof(word)*(numSymbols+1));
    }
  symbols[numSymbols] = (char*)malloc(strlen(symbol)+1);
  symbolFile[numSymbols] = (char*)malloc(strlen(file)+1);
  strcpy(symbols[numSymbols], symbol);
  strcpy(symbolFile[numSymbols], file);
  symbolValues[numSymbols++] = value;
  return -1;
  }

