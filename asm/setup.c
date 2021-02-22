#include "header.h"

void setup() {
  opcode("CALL", "W",  "D4 hi(1) lo(1)");
  opcode("RTN",  "",   "D5");
  opcode("FILDES","W", "00 00 00 00 hi(1) lo(1) 00 00 00 00 00 00 00 00 00 00 00 00 00");
  opcode("ADD",  "R,R","8/2 73 60 8/1 F4 A/1 9/2 73 60 9/1 74 B/1");
  opcode("ADD",  "R,W","8/1 FC lo(2) A/1 9/1 7C hi(2) B/1");
  opcode("ADC",  "R,R","8/2 73 60 8/1 74 A/1 9/2 73 60 9/1 74 B/1");
  opcode("ADC",  "R,W","8/1 7C lo(2) A/1 9/1 7C hi(2) B/1");
  opcode("AND",  "R,R","8/2 73 60 8/1 F2 A/1 9/2 73 60 9/1 F2 B/1");
  opcode("AND",  "R,W","8/1 FA lo(2) A/1 9/1 FA hi(2) B/1");
  opcode("BNZ",  "R,P","8/1 3A lo(2) 9/1 3A lo(2)");
  opcode("BZ",   "R,P","8/1 73 60 9/1 F1 32 lo(2)");
//  opcode("DBNZ", "R,P","2/1 8/1 3A lo(2) 9/1 3A lo(2)");
//  opcode("DLBNZ","R,W","2/1 8/1 CA hi(2) lo(2) 9/1 CA hi(2) lo(2)");
  opcode("LBNZ", "R,W","8/1 CA hi(2) lo(2) 9/1 CA hi(2) lo(2)");
  opcode("LBZ",  "R,W","8/1 73 60 9/1 F1 C2 hi(2) lo(2)");
  opcode("MOV",  "R,R","8/2 A/1 9/2 B/1");
  opcode("MOV",  "R,W","F8 lo(2) A/1 F8 hi(2) B/1");
  opcode("OR",   "R,R","8/2 73 60 8/1 F1 A/1 9/2 73 60 9/1 F1 B/1");
  opcode("OR",   "R,W","8/1 F9 lo(2) A/1 9/1 F9 hi(2) B/1");
  opcode("PUSH", "N",  "8/1 73 9/1 73 ");
  opcode("POP",  "N",  "60 72 B/1 F0 A/1");
  opcode("SHL",  "R",  "8/1 FE A/1 9/1 7E B/1");
  opcode("SHLC", "R",  "8/1 7E A/1 9/1 7E B/1");
  opcode("SHR",  "R",  "9/1 F6 B/1 8/1 76 A/1");
  opcode("SHRC", "R",  "9/1 76 B/1 8/1 76 A/1");
  opcode("SBB",  "R,R","8/2 73 60 8/1 77 A/1 9/2 73 60 9/1 77 B/1");
  opcode("SBB",  "R,W","8/1 7F lo(2) A/1 9/1 7F hi(2) B/1");
  opcode("SUB",  "R,R","8/2 73 60 8/1 F7 A/1 9/2 73 60 9/1 77 B/1");
  opcode("SUB",  "R,W","8/1 FF lo(2) A/1 9/1 7F hi(2) B/1");
  opcode("XOR",  "R,R","8/2 73 60 8/1 F3 A/1 9/2 73 60 9/1 F3 B/1");
  opcode("XOR",  "R,W","8/1 FB lo(2) A/1 9/1 FB hi(2) B/1");
  opcode("ZERO", "R",  "F8 00 A/1 B/1");
  opcode("ADD",  "",   "F4");
  opcode("ADC",  "",   "74");
  opcode("ADCI", "B",  "7C /1");
  opcode("ADI",  "B",  "FC /1");
  opcode("AND",  "",   "F2");
  opcode("ANI",  "B",  "FA /1");
  opcode("B1",   "P",  "34 /1");
  opcode("B2",   "P",  "35 /1");
  opcode("B3",   "P",  "36 /1");
  opcode("B4",   "P",  "37 /1");
  opcode("BDF",  "P",  "33 /1");
  opcode("BGE",  "P",  "33 /1");
  opcode("BL",   "P",  "3B /1");
  opcode("BM",   "P",  "3B /1");
  opcode("BN1",  "P",  "3C /1");
  opcode("BN2",  "P",  "3D /1");
  opcode("BN3",  "P",  "3E /1");
  opcode("BN4",  "P",  "3F /1");
  opcode("BNF",  "P",  "3B /1");
  opcode("BNQ",  "P",  "39 /1");
  opcode("BNZ",  "P",  "3A /1");
  opcode("BPZ",  "P",  "33 /1");
  opcode("BQ",   "P",  "31 /1");
  opcode("BR",   "P",  "30 /1");
  opcode("BZ",   "P",  "32 /1");
  opcode("DEC",  "R",  "2/1");
  opcode("DEC",  "N",  "2/1");
  opcode("DIS",  "",   "71");
  opcode("GHI",  "R",  "9/1");
  opcode("GHI",  "N",  "9/1");
  opcode("GLO",  "R",  "8/1");
  opcode("GLO",  "N",  "8/1");
  opcode("IDL",  "",   "00");
  opcode("INC",  "R",  "1/1");
  opcode("INC",  "N",  "1/1");
  opcode("INP",  "7",  "68|1");
  opcode("IRX",  "",   "60");
  opcode("LBDF", "W",  "C3 hi(1) lo(1)");
  opcode("LBNF", "W",  "CB hi(1) lo(1)");
  opcode("LBNQ", "W",  "C9 hi(1) lo(1)");
  opcode("LBNZ", "W",  "CA hi(1) lo(1)");
  opcode("LBQ",  "W",  "C1 hi(1) lo(1)");
  opcode("LBR",  "W",  "C0 hi(1) lo(1)");
  opcode("LBZ",  "W",  "C2 hi(1) lo(1)");
  opcode("LDA",  "R",  "4/1");
  opcode("LDA",  "N",  "4/1");
  opcode("LDI",  "B",  "F8 /1");
  opcode("LDN",  "R",  "0/1");
  opcode("LDN",  "N",  "0/1");
  opcode("LDX",  "",   "F0");
  opcode("LDXA", "",   "72");
  opcode("LSDF", "",   "CF");
  opcode("LSIE", "",   "CC");
  opcode("LSKP", "",   "C8");
  opcode("LSNF", "",   "C7");
  opcode("LSNQ", "",   "C5");
  opcode("LSNZ", "",   "C6");
  opcode("LSQ",  "",   "CD");
  opcode("LSZ",  "",   "CE");
  opcode("MARK", "",   "79");
  opcode("NBR",  "",   "38");
  opcode("NLBR", "",   "C8");
  opcode("NOP",  "",   "C4");
  opcode("OR",   "",   "F1");
  opcode("ORI",  "B",  "F9 /1");
  opcode("OUT",  "7",  "60|1");
  opcode("PHI",  "R",  "B/1");
  opcode("PHI",  "N",  "B/1");
  opcode("PLO",  "R",  "A/1");
  opcode("PLO",  "N",  "A/1");
  opcode("REQ",  "",   "7A");
  opcode("RET",  "",   "70");
  opcode("RSHL", "",   "7E");
  opcode("RSHR", "",   "76");
  opcode("SAV",  "",   "78");
  opcode("SD",   "",   "F5");
  opcode("SDB",  "",   "75");
  opcode("SDBI", "B",  "7D /1");
  opcode("SDI",  "B",  "FD /1");
  opcode("SEP",  "R",  "D/1");
  opcode("SEP",  "N",  "D/1");
  opcode("SEQ",  "",   "7B");
  opcode("SEX",  "R",  "E/1");
  opcode("SEX",  "N",  "E/1");
  opcode("SHL",  "",   "FE");
  opcode("SHLC", "",   "7E");
  opcode("SHR",  "",   "F6");
  opcode("SHRC", "",   "76");
  opcode("SKP",  "",   "38");
  opcode("SM",   "",   "F7");
  opcode("SMB",  "",   "77");
  opcode("SMBI", "B",  "7F /1");
  opcode("SMI",  "B",  "FF /1");
  opcode("STR",  "R",  "5/1");
  opcode("STR",  "N",  "5/1");
  opcode("STXD", "",   "73");
  opcode("XOR",  "",   "F3");
  opcode("XRI",  "B",  "FB /1");
  opcode("ORG",  "W",  "*ORG");
  opcode("END",  "W",  "*END");
  opcode("DB",   "M",  "*DB");
  opcode("DW",   "M",  "*DW");
  opcode("DS",   "W",  "*DS");
  opcode("EQU",  "W",  "*EQU");
  opcode("PUBLIC", "L", "*PUBLIC");
  opcode("PROC", "",    "*PROC");
  opcode("ENDP", "",    "*ENDP");
  opcode("EXTERN", "",  "*EXTERN");
  opcode("ID",     "P", "*ID");
  opcode("EXEC",  "W,W,W", "*EXEC");
  }