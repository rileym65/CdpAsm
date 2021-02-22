#include "header.h"
#include <fcntl.h>
#include <unistd.h>

void outputBin() {
  int outfile;
  word len;
  byte buffer[6];
  len = 1 + highest - lowest;
  outfile = open(outName, O_CREAT | O_TRUNC | O_WRONLY, 0666);
  if (outfile < 0) {
    printf("Error: Could not open output file: %s\n",outName);
    return;
    }
  if (elfos) {
    buffer[0] = (lowest & 0xff00) >> 8;
    buffer[1] = lowest & 0xff;
    buffer[2] = (len & 0xff00) >> 8;
    buffer[3] = len & 0xff;
    buffer[4] = (execAddress & 0xff00) >> 8;
    buffer[5] = execAddress & 0xff;
    write(outfile, buffer, 6);
    }
  write(outfile, memory+lowest, len);
  close(outfile);
  }

