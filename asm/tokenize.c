#include "header.h"

int tokenize(char* line) {
  int i;
  int pos;
  int hex;
  int v;
  char temp[32];
  char tmp[256];
  numTokens = 0;
  pos = 0;
  while (line[pos] != 0) {
    while (line[pos] == ' ' || line[pos] == '\t') pos++;

    if (line[pos] == '$' && ((line[pos+1] >= '0' && line[pos+1] <= '9') ||
                             (line[pos+1] >= 'a' && line[pos+1] <= 'f') ||
                             (line[pos+1] >= 'A' && line[pos+1] <= 'F') )) {
      pos++;
      i = 0;
      hex = 0;
      while ((line[pos] >= '0' && line[pos] <= '9') ||
             (line[pos] >= 'a' && line[pos] <= 'f') ||
             (line[pos] >= 'A' && line[pos] <= 'F')) {
        if (line[pos] >= 'a' && line[pos] <= 'f') hex = 1;
        if (line[pos] >= 'A' && line[pos] <= 'F') hex = 1;
        temp[i++] = line[pos++];
        }
      temp[i] = 0;
      if ((line[pos] >= 'g' && line[pos] <= 'z') ||
          (line[pos] >= 'G' && line[pos] <= 'Z')) {
        showError("Invalid hex constant");
        return 0;
        }
      tokens[numTokens++] = fromHex(temp);
      }

    else if (line[pos] == '$') {
      tokens[numTokens++] = address;
      pos++;
      }

    else if (line[pos] == '%' && (line[pos+1] >= '0' && line[pos+1] <= '1')) {
      pos++;
      i = 0;
      while ((line[pos] >= '0' && line[pos] <= '1') || line[pos] == '_') {
        if (line[pos] != '_') temp[i++] = line[pos++];
          else pos++;
        }
      temp[i] = 0;
      if ((line[pos] >= 'a' && line[pos] <= 'z') ||
          (line[pos] >= '2' && line[pos] <= '9') ||
          (line[pos] >= 'A' && line[pos] <= 'Z')) {
        showError("Invalid binary constant");
        return 0;
        }
      tokens[numTokens++] = fromBinary(temp);
      }

    else if (line[pos] >= '0' && line[pos] <= '9') {
      i = 0;
      hex = 0;
      while ((line[pos] >= '0' && line[pos] <= '9') ||
             (line[pos] >= 'a' && line[pos] <= 'f') ||
             (line[pos] >= 'A' && line[pos] <= 'F')) {
        if (line[pos] >= 'a' && line[pos] <= 'f') hex = 1;
        if (line[pos] >= 'A' && line[pos] <= 'F') hex = 1;
        temp[i++] = line[pos++];
        }
      temp[i] = 0;
      if (hex == 1 && line[pos] != 'H' && line[pos] != 'h') {
        showError("Invalid hex constant");
        return 0;
        }
      if (hex == 1) {
        tokens[numTokens++] = fromHex(temp);
        pos++;
        }
      else if (line[pos] == 'h' || line[pos] == 'H') {
        tokens[numTokens++] = fromHex(temp);
        pos++;
        }
      else {
        tokens[numTokens++] = fromDec(temp);
        }
      }

    else if (line[pos] == '\'') {
      pos ++;
      while (line[pos] != '\'') {
        if (line[pos] == 0) {
          showError("Unexpected end of line");
          return 0;
          }
        tokens[numTokens++] = line[pos++];
        }
      pos++;
      }

    else if (line[pos] == '+' || line[pos] == '-' ||
             line[pos] == '*' || line[pos] == '/' ||
             line[pos] == '|' || line[pos] == '&' ||
             line[pos] == '(' || line[pos] == ')' ||
             line[pos] == '^' || line[pos] == '.') {
      tokens[numTokens++] = line[pos++] + FLG_OP;
      }

    else if ((line[pos] == 'l' || line[pos] == 'L') &&
             (line[pos+1] == 'o' || line[pos+1] == 'O') &&
             (line[pos+2] == 'w' || line[pos+2] == 'W')) {
      tokens[numTokens++] = 'L' + FLG_OP;
      pos += 3;
      }

    else if ((line[pos] == 'h' || line[pos] == 'H') &&
             (line[pos+1] == 'i' || line[pos+1] == 'I') &&
             (line[pos+2] == 'g' || line[pos+2] == 'H') &&
             (line[pos+3] == 'h' || line[pos+3] == 'H')) {
      tokens[numTokens++] = 'H' + FLG_OP;
      pos += 4;
      }

    else if (isRReg(line+pos) >= 0) {
      tokens[numTokens++] = isRReg(line+pos) | FLG_R;
      pos+=2;
      if (line[pos] >= '0' && line[pos] <= '9') pos++;
      }

    else if ((line[pos] >= 'a' && line[pos] <= 'z') ||
             (line[pos] >= 'A' && line[pos] <= 'Z')) {
      i = 0;
      while ((line[pos] >= 'a' && line[pos] <= 'z') ||
             (line[pos] >= 'A' && line[pos] <= 'Z') ||
             (line[pos] >= '0' && line[pos] <= '9') ||
             line[pos] == '_') {
        temp[i++] = line[pos++];
        }
        temp[i] = 0;
        v = lookupLabel(temp);
        if (v >= 0) tokens[numTokens++] = v;
        else tokens[numTokens++] = FLG_UNDEF;
        if (pass == 2 && v < 0) {
          sprintf(tmp,"Label not found: %s",temp);
          showError(tmp);
          }
        if (pass == 2) {
          v = findLabel(temp);
          if (v >= 0) {
            if (labelFlags[v] & LFLAGS_EXTERN) {
              sprintf(externs[externsCount++],"%d|%s",argCount,temp);
              }
            if (labelUsedCount[v] == 0)
              labelUsed[v] = (UInt32*)malloc(sizeof(UInt32));
            else
              labelUsed[v] = (UInt32*)realloc(labelUsed[v],sizeof(UInt32) * (labelUsedCount[v]+1));
            labelUsed[v][labelUsedCount[v]] = lineNumber;
            labelUsedCount[v]++;
            }
          }
      }

    else if (line[pos] == 0) {
      }

    else if (line[pos] == ';') {
      while (line[pos] != 0) pos++;
      }

    else {
      showError("Cannot parse line");
      return 0;
      }
    }
  return -1;
  }
