#include "header.h"

int parse(char* line) {
  int i;
  int pos;
  int qt;
  int flag;
  char temp[256];
  strcpy(op,"");
  strcpy(label,"");
  argCount = 0;
  pos = 0;
  externsCount = 0;
  if (line[0] == 0) return 0;
  if ((line[0] >= 'a' && line[0] <= 'z') ||
      (line[0] >= 'A' && line[0] <= 'Z')) {
    while (line[pos] != 0 && line[pos] != ' ' && line[pos] != '\t' &&
           line[pos] != ':') {
      label[pos] = line[pos];
      pos++;
      }
    label[pos] = 0;
    if (line[pos] != ':') return ERR_INV_LABEL;
    pos++;
    }
  while (line[pos] == ' ' || line[pos] == '\t') pos++;
  if (line[pos] == ';') return 0;
  if (line[pos] == 0) return 0;
  i = 0;
  while (line[pos] != ' ' && line[pos] != '\t' && line[pos] != 0)
    op[i++] = line[pos++];
  op[i] = 0;
  while (line[pos] != 0) {
    while (line[pos] == ' ' || line[pos] == '\t') pos++;
    if (line[pos] == 0) return 0;
    if (line[pos] == ';') return 0;
    if (line[pos] == '\'' && line[pos+2] != '\'') {
      pos++;
      while (line[pos] != 0 && line[pos] != '\'') {
        args[argCount++] = line[pos++];
        }
      if (line[pos] == '\'') pos++;
      while (line[pos] == ' ' || line[pos] == '\t') pos++;
      if (line[pos] == ',') pos++;
      }
    else {
      i = 0;
      qt = 0;
      flag = -1;
      while (flag) {
        if (line[pos] == 0) flag = 0;
        if (qt == 0 && line[pos] == ';') flag = 0;
        if (qt == 0 && line[pos] == ',') flag = 0;
        if (line[pos] == '\'') qt ^= 1;
        if (flag) temp[i++] = line[pos++];
        }
      temp[i] = 0;
      strcpy(argsAscii[argCount],temp);
      args[argCount] = evaluate(temp);
      argCount++;
      if (line[pos] == ',') pos++;
      }
    }
if (externsCount > 0) {
for (i=0; i<externsCount; i++) printf("extern: %s\n",externs[i]);
}
  return -1;
  }
