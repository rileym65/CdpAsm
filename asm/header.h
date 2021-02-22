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
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define VERSION  "1.0"

#define ERR_INV_LABEL            1

#define FLG_R                    0x80000000
#define FLG_UNDEF                0x40000000
#define FLG_OP                   0x20000000

#define ARG_NUMBER               0
#define ARG_LOCAL                1
#define ARG_EXTERN               2

#define LFLAGS_EXTERN            1

typedef unsigned char byte;
typedef u_int16_t word;
typedef u_int32_t UInt32;
typedef int32_t   Int32;

LINK char o_opcodes[255][32];
LINK char o_args[255][32];
LINK int  o_argCount[255];
LINK char o_trans[255][255];
LINK int  numOpcodes;

LINK char   label[64];
LINK char   op[16];
LINK UInt32 args[255];
LINK char   argsAscii[255][255];
LINK int    argCount;

LINK char   externs[32][64];
LINK int    externsCount;

LINK char **defines;
LINK char **defineValues;
LINK int    defineCount;

LINK char **publics;
LINK int    publicsCount;

LINK int    pass;
LINK word   address;
LINK int    curAddress;
LINK word   highest;
LINK word   lowest;
LINK word   startAddress;
LINK int    lineNumbers[255];
LINK int    lineNumberSP;
LINK int    lineNumber;
LINK byte   memory[65536];
LINK int    errors;
LINK int    linesRead;
LINK char   tmp[255];
LINK int    codeGenerated;
LINK int    showList;
LINK int    showXref;
LINK char   sourceName[2048];
LINK char   destName[2048];
LINK char   baseName[2048];
LINK int    outCount;
LINK FILE  *outFile;
LINK int    verbose;

LINK char   **labels;
LINK UInt32  *labelValues;
LINK word    *labelFlags;
LINK UInt32  *labelLine;
LINK int      labelCount;
LINK UInt32 **labelUsed;
LINK UInt32  *labelUsedCount;

LINK UInt32 tokens[255];
LINK int    numTokens;

LINK byte   codes[256];
LINK int    numCodes;

LINK FILE*  files[256];
LINK int    currentFile;

LINK char   line[1024];
LINK char   rawLine[1024];

extern void   addDefine(char* l,char* v);
extern int    assemble(char* line);
extern int    assemblyPass(int p);
extern UInt32 evaluate(char* line);
extern int    findDefine(char* l);
extern int    findLabel(char* l);
extern void   flush();
extern word   fromBinary(char* num);
extern word   fromDec(char* num);
extern word   fromHex(char* num);
extern int    preIf(char* line);
extern int    isRReg(char* msg);
extern char*  lookupDefine(char* l);
extern int    lookupLabel(char* l);
extern int    lookupOpcode();
extern void   opcode(char* o, char* a, char* t);
extern void   output(byte b);
extern int    parse(char* line);
extern int    readFile();
extern int    readLine();
extern void   reduce(int start, int end);
extern void   setup();
extern void   setup1805(int variant);
extern void   showError(char* message);
extern int    tokenize(char* line);
extern void   undef(char* l);

#endif

