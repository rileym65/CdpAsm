#ifndef _HEADER_H
#define _HEADER_H

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef unsigned char byte;
typedef u_int16_t     word;
typedef u_int32_t     UInt32;
typedef int32_t       Int32;

LINK int     elfos;
LINK word    execAddress;
LINK int     errors;
LINK char  **files;
LINK word    highest;
LINK word    lowest;
LINK byte    memory[65536];
LINK int     numFiles;
LINK int     numSymbols;
LINK word    outAddress;
LINK byte    outBytes[16];
LINK int     outCount;
LINK FILE   *outfile;
LINK char    outName[128];
LINK char    outputMode;
LINK char  **symbols;
LINK char  **symbolFile;
LINK word   *symbolValues;
LINK byte    used[65536];
LINK int     verbose;

extern int  addSymbol(char* symbol, word value, char* file);
extern void cleanup();
extern int  loadFile(int index);
extern void outputBin();
extern void outputHex();
extern void outputRcs();

#endif

