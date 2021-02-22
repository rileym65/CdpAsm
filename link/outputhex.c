#include "header.h"

void hexOutLine() {
  int i;
  byte check;
  if (outCount > 0) {
    fprintf(outfile,":%02X%04X00",outCount,outAddress);
    check = outCount;
    check += ((outAddress & 0xff00) >> 8);
    check += (outAddress & 0xff);
    for (i=0; i<outCount; i++) {
      fprintf(outfile,"%02X",outBytes[i]);
      check += outBytes[i];
      }
    check = (~check) + 1;
    fprintf(outfile,"%02X\n",check);
    outCount = 0;
    }
  }

void hexOut(word a, byte b) {
  if (a != outAddress+outCount) {
    if (outCount > 0) {
      hexOutLine();
      }
    outAddress = a;
    }
  outBytes[outCount++] = b;
  if (outCount == 16) {
    hexOutLine();
    outAddress += 16;
    outCount = 0;
    }
  }

void outputHex() {
  int   i;
  word  len;
  byte  check;
  len = 1 + highest - lowest;
  if ((outfile = fopen(outName,"w")) == NULL) {
    printf("Error: Could not open output file: %s\n",outName);
    return;
    }
  outCount = 0;
  outAddress = lowest;
  if (elfos) {
    outAddress -= 6;
    hexOut(outAddress+0,(lowest & 0xff00) >> 8);
    hexOut(outAddress+1,lowest & 0xff);
    hexOut(outAddress+2,(len & 0xff00) >> 8);
    hexOut(outAddress+3,len & 0xff);
    hexOut(outAddress+4,(execAddress & 0xff00) >> 8);
    hexOut(outAddress+5,execAddress & 0xff);
    }
  for (i=lowest; i<=highest; i++) {
    if (used[i] != 0) hexOut(i,memory[i]);
    }
  if (outCount > 0) {
    hexOutLine();
    }
  if (execAddress != 0xffff) {
    check = 9;
    check += ((execAddress & 0xff00) >> 8);
    check += (execAddress & 0xff);
    check = (~check) + 1;
    fprintf(outfile,":04000005%08x%02x\n",execAddress,check);
    }
  fprintf(outfile,":00000001FF\n");
  fclose(outfile);
  }

