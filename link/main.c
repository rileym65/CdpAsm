#define MAIN

#include "header.h"

int main(int argc, char** argv) {
  int i;
  int j;
  lowest = 0xffff;
  highest = 0x0000;
  elfos = 0;
  verbose = 0;
  numFiles = 0;
  numSymbols = 0;
  execAddress = 0xffff;
  errors = 0;
  outputMode = 'R';
  strcpy(outName,"");
  for (i=0; i<65536; i++) {
    memory[i] = 0;
    used[i] = 0;
    }
  if (argc < 2) {
    printf("Usage: cdplink {options} file1 file2 ... filen\n");
    exit(1);
    }
  i = 1;
  while (i < argc) {
    if (strcmp(argv[i],"-b") == 0) outputMode = 'B';
    else if (strcmp(argv[i],"-e") == 0) elfos = -1;
    else if (strcmp(argv[i],"-i") == 0) outputMode = 'I';
    else if (strcmp(argv[i],"-r") == 0) outputMode = 'R';
    else if (strcmp(argv[i],"-v") == 0) verbose = -1;
    else {
      if (numFiles == 0)
        files = (char**)malloc(sizeof(char*));
      else
        files = (char**)realloc(files,sizeof(char*) * (numFiles+1));
      files[numFiles] = (char*)malloc(strlen(argv[i]) + 1);
      strcpy(files[numFiles++], argv[i]);
      if (strlen(outName) == 0) {
        strcpy(outName, files[numFiles-1]);
        for (j=0; j<strlen(outName); j++)
          if (outName[j] == '.') outName[j] = 0;
        strcat(outName,"_");
        }
      }
    i++;
    }
  if (numFiles == 0) {
    printf("No object files specified.\n");
    exit(1);
    }

  if (outputMode == 'I') strcat(outName,".hex");
  if (outputMode == 'B') strcat(outName,".bin");
  if (outputMode == 'R') strcat(outName,".prg");

  for (i=0; i<numFiles; i++) {
    if (loadFile(i) == 0) {
      cleanup();
      printf("Link aborted due to errors.\n");
      exit(1);
      }
    }

  if (errors > 0) {
    cleanup();
    printf("Output not generated due to errors\n");
    printf("Error count: %d\n",errors);
    exit(1);
    }

  if (outputMode == 'B') outputBin();
  if (outputMode == 'R') outputRcs();
  if (outputMode == 'I') outputHex();

  if (verbose) {
    printf("\n");
    printf("Lowest  : %04x\n",lowest);
    printf("Highest : %04x\n",highest);
    printf("Exec    : ");
    if (execAddress == 0xffff) printf("Not specified\n");
      else printf("%04x\n",execAddress);
    printf("Out file: %s\n",outName);
    printf("\n");
    printf("Public symbols:\n");
    for (i=0; i<numSymbols; i++) {
      printf("  %04x: ",symbolValues[i]);
      printf("%-20s ",symbols[i]);
      printf("%s\n",symbolFile[i]);
      }
    printf("\n");
    }

  cleanup();

  return 0;
  }

