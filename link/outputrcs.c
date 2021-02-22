#include "header.h"

void rcsOut(word a, byte b) {
  int i;
  if (a != outAddress+outCount) {
    if (outCount > 0) {
      fprintf(outfile,":%04x",outAddress);
      for (i=0; i<outCount; i++)
        fprintf(outfile," %02x",outBytes[i]);
      fprintf(outfile,"\n");
      outCount = 0;
      outAddress = a;
      }
    else outAddress = a;
    }
  outBytes[outCount++] = b;
  if (outCount == 16) {
    fprintf(outfile,":%04x",outAddress);
    for (i=0; i<16; i++)
      fprintf(outfile," %02x",outBytes[i]);
    fprintf(outfile,"\n");
    outAddress += 16;
    outCount = 0;
    }
  }

void outputRcs() {
  int   i;
  word  len;
  len = 1 + highest - lowest;
  if ((outfile = fopen(outName,"w")) == NULL) {
    printf("Error: Could not open output file: %s\n",outName);
    return;
    }
  outCount = 0;
  outAddress = lowest;
  if (elfos) {
    outAddress -= 6;
    rcsOut(outAddress+0,(lowest & 0xff00) >> 8);
    rcsOut(outAddress+1,lowest & 0xff);
    rcsOut(outAddress+2,(len & 0xff00) >> 8);
    rcsOut(outAddress+3,len & 0xff);
    rcsOut(outAddress+4,(execAddress & 0xff00) >> 8);
    rcsOut(outAddress+5,execAddress & 0xff);
    }
  for (i=lowest; i<=highest; i++) {
    if (used[i] != 0) rcsOut(i,memory[i]);
    }
  if (outCount > 0) {
    fprintf(outfile,":%04x",outAddress);
    for (i=0; i<outCount; i++)
      fprintf(outfile," %02x",outBytes[i]);
    fprintf(outfile,"\n");
    }
  if (execAddress != 0xffff) 
    fprintf(outfile,"*%04x\n",execAddress);
  fclose(outfile);
  }

