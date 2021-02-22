#include "header.h"

void setup1805(int variant) {
  opcode("RLDI",  "N,W",  "68 C/1 hi(2) lo(2)");
  opcode("RLXA",  "N",    "68 6/1");
  opcode("RSXD",  "N",    "68 A/1");
  opcode("RNX",   "N",    "68 B/1");
  opcode("BCI",   "P",    "68 3E /1");
  opcode("BXI",   "P",    "68 3F /1");
  opcode("LDC",   "",     "68 06");
  opcode("GEC",   "",     "68 08");
  opcode("STPC",  "",     "68 00");
  opcode("DTC",   "",     "68 01");
  opcode("STM",   "",     "68 07");
  opcode("SCM1",  "",     "68 05");
  opcode("SCM2",  "",     "68 03");
  opcode("SPM1",  "",     "68 04");
  opcode("SPM2",  "",     "68 02");
  opcode("ETQ",   "",     "68 09");
  opcode("XIE",   "",     "68 0A");
  opcode("XID",   "",     "68 0B");
  opcode("CIE",   "",     "68 0C");
  opcode("CID",   "",     "68 0D");
  opcode("SCAL",  "N,W",  "68 8/1 hi(2) lo(2)");
  opcode("SRET",  "N",    "68 9/1");
  if (variant == 1) {
    opcode("DBNZ",  "N,W",  "68 2/1 hi(2) lo(2)");
    opcode("DADD",  "",     "68 F4");
    opcode("DADI",  "B",    "68 FC /1");
    opcode("DADC",  "",     "68 74");
    opcode("DACI",  "B",    "68 7C /1");
    opcode("DSM",   "",     "68 F7");
    opcode("DSMI",  "B",    "68 FF /1");
    opcode("DSMB",  "",     "68 77");
    opcode("DSBI",  "B",    "68 7F /1");
    opcode("DSAV",  "",     "68 76");
    }
  }

