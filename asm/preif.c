#include "header.h"

#define PRE_UNDEF        0x80000000
#define PRE_DEFINED      0x80010000
#define PRE_OR           0x80020000
#define PRE_AND          0x80030000
#define PRE_GT           0x80040000
#define PRE_GE           0x80050000
#define PRE_LT           0x80060000
#define PRE_LE           0x80070000
#define PRE_EQ           0x80080000
#define PRE_NE           0x80090000
#define PRE_PL           0x800a0000
#define PRE_MN           0x800b0000
#define PRE_ML           0x800c0000
#define PRE_DV           0x800d0000
#define PRE_OP           0x800e0000
#define PRE_CP           0x800f0000
#define PRE_EX           0x80100000

Int32  preTokens[255];
UInt32 preTokenCount;

void preTokenize(char* line) {
  int i;
  preTokenCount = 0;
  char token[64];
  while (*line != 0) {
    while (*line == ' ' || *line == '\t') line++;
    if (strncasecmp(line,"defined",7) == 0) {
      preTokens[preTokenCount++] = PRE_DEFINED;
      line += 7;
      }
    else if (strncasecmp(line,"||",2) == 0) {
      preTokens[preTokenCount++] = PRE_OR;
      line += 2;
      }
    else if (strncasecmp(line,"&&",2) == 0) {
      preTokens[preTokenCount++] = PRE_AND;
      line += 2;
      }
    else if (strncasecmp(line,">=",2) == 0) {
      preTokens[preTokenCount++] = PRE_GE;
      line += 2;
      }
    else if (strncasecmp(line,"<=",2) == 0) {
      preTokens[preTokenCount++] = PRE_LE;
      line += 2;
      }
    else if (strncasecmp(line,"!=",2) == 0) {
      preTokens[preTokenCount++] = PRE_NE;
      line += 2;
      }
    else if (strncasecmp(line,"==",2) == 0) {
      preTokens[preTokenCount++] = PRE_EQ;
      line += 2;
      }
    else if (*line == '>') {
      preTokens[preTokenCount++] = PRE_GT;
      line += 1;
      }
    else if (*line == '<') {
      preTokens[preTokenCount++] = PRE_LT;
      line += 1;
      }
    else if (*line == '+') {
      preTokens[preTokenCount++] = PRE_PL;
      line += 1;
      }
    else if (*line == '-') {
      preTokens[preTokenCount++] = PRE_MN;
      line += 1;
      }
    else if (*line == '*') {
      preTokens[preTokenCount++] = PRE_ML;
      line += 1;
      }
    else if (*line == '/') {
      preTokens[preTokenCount++] = PRE_DV;
      line += 1;
      }
    else if (*line == '(') {
      preTokens[preTokenCount++] = PRE_OP;
      line += 1;
      }
    else if (*line == ')') {
      preTokens[preTokenCount++] = PRE_CP;
      line += 1;
      }
    else if (*line == '!') {
      preTokens[preTokenCount++] = PRE_EX;
      line += 1;
      }
    else if (*line >= '0' && *line <= '9') {
      i = 0;
      while (*line >= '0' && *line <= '9') token[i++] = *line++;
      token[i] = 0;
      preTokens[preTokenCount++] = fromDec(token);
      }
    else if (*line == '$') {
      i = 0;
      line++;
      while ((*line >= '0' && *line <= '9') ||
             (*line >= 'a' && *line <= 'f') ||
             (*line >= 'A' && *line <= 'F')) token[i++] = *line++;
      token[i] = 0;
      preTokens[preTokenCount++] = fromHex(token);
      }
    else if (*line == '%') {
      i = 0;
      line++;
      while (*line == '0' || *line <= '1' || *line == '_') token[i++] = *line++;
      token[i] = 0;
      preTokens[preTokenCount++] = fromBinary(token);
      }
    else if ((*line >= 'a' && *line <= 'z') ||
             (*line >= 'A' && *line <= 'Z') ||
             *line == '_') {
      i = 0;
      while ((*line >= 'a' && *line <= 'z') ||
             (*line >= 'A' && *line <= 'Z') ||
             (*line >= '0' && *line <= '9') ||
             *line == '_') token[i++] = *line++;
      token[i] = 0;
      if (findDefine(token) >= 0)
        preTokens[preTokenCount++] = atoi(lookupDefine(token));
      else
        preTokens[preTokenCount++] = PRE_UNDEF;
      }
    else {
      showError("Invalid expression in #if");
      exit(1);
      }
    }
  }

void preReduce(int start, int end) {
  int i;
  int pos;
  int flag;
  int pflag;
  int op;
  int cp;
  flag = -1;
  while (flag) {
    flag = 0;

    /* ********************************* */
    /* ***** Check for parenthesis ***** */
    /* ********************************* */
    pflag = -1;
    while (pflag) {
      pflag = 0;
      op = -1;
      cp = -1;
      pos = start;
      while (pos <= end) {
        if (preTokens[pos] == PRE_OP) op = pos;
        if (preTokens[pos] == PRE_CP) {
          cp = pos;
          pos = end;
          }
        pos++;
        }
      if (op >= 0) {
        if (cp < 0) {
          showError("Expression error");
          exit(1);
          }
        for (i=op; i<preTokenCount-1; i++) preTokens[i] = preTokens[i+1];
        end--;
        preTokenCount--;
        cp--;
        for (i=cp; i<preTokenCount-1; i++) preTokens[i] = preTokens[i+1];
        end--;
        preTokenCount--;
        cp--;
        preReduce(op,cp);
        end = preTokenCount - 1;
        pflag = -1;
        }
      }

    /* ***************************** */
    /* ***** Check for defined ***** */
    /* ***************************** */
    pos = start;
    while (pos <= end) {
      if (preTokens[pos] == PRE_DEFINED && pos < end) {
        if (preTokens[pos+1] == PRE_UNDEF) {
          preTokens[pos] = 0;
          for (i=pos+1; i<end-1; i++)
            preTokens[i] = preTokens[i+1];
          end--;
          preTokenCount--;
          flag = -1;
          }
        else if (preTokens[pos+1] < 0x80000000) {
          preTokens[pos] = -1;
          for (i=pos+1; i<end-1; i++)
            preTokens[i] = preTokens[i+1];
          end--;
          preTokenCount--;
          flag = -1;
          }
        }
      pos++;
      }

    /* *********************** */
    /* ***** Check for ! ***** */
    /* *********************** */
    pos = start;
    while (pos <= end) {
      if (preTokens[pos] == PRE_EX && pos < end) {
        if (preTokens[pos+1] < 0x80000000) {
          preTokens[pos] = (preTokens[pos]) ? 0 : -1;
          for (i=pos+1; i<end-1; i++)
            preTokens[i] = preTokens[i+1];
          end--;
          preTokenCount--;
          flag = -1;
          }
        }
      pos++;
      }

    /* **************************** */
    /* ***** Check for * and / **** */
    /* **************************** */
    pos = start;
    while (pos <= end) {
      if (pos > start && preTokens[pos] == PRE_ML && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] * preTokens[pos+1]) &0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          }
        }
      if (pos > start && preTokens[pos] == PRE_DV && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] / preTokens[pos+1]) &0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          }
        }
      pos++;
      }

    /* **************************** */
    /* ***** Check for + and - **** */
    /* **************************** */
    pos = start;
    while (pos <= end) {
      if (pos > start && preTokens[pos] == PRE_PL && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] + preTokens[pos+1]) &0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          }
        }
      if (pos > start && preTokens[pos] == PRE_MN && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] - preTokens[pos+1]) &0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          }
        }
      pos++;
      }

    /* ******************************** */
    /* ***** Check for comparisons **** */
    /* ******************************** */
    pos = start;
    while (pos <= end) {
      if (pos > start && preTokens[pos] == PRE_GT && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] > preTokens[pos+1]) ? -1 : 0;
          preTokens[pos-1] &= 0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      if (pos > start && preTokens[pos] == PRE_GE && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] >= preTokens[pos+1]) ? -1 : 0;
          preTokens[pos-1] &= 0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      if (pos > start && preTokens[pos] == PRE_LT && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] < preTokens[pos+1]) ? -1 : 0;
          preTokens[pos-1] &= 0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      if (pos > start && preTokens[pos] == PRE_LE && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] <= preTokens[pos+1]) ? -1 : 0;
          preTokens[pos-1] &= 0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      if (pos > start && preTokens[pos] == PRE_EQ && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] == preTokens[pos+1]) ? -1 : 0;
          preTokens[pos-1] &= 0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      if (pos > start && preTokens[pos] == PRE_NE && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] != preTokens[pos+1]) ? -1 : 0;
          preTokens[pos-1] &= 0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      pos++;
      }

    /* ****************************** */
    /* ***** Check for || and && **** */
    /* ****************************** */
    pos = start;
    while (pos <= end) {
      if (pos > start && preTokens[pos] == PRE_OR && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] | preTokens[pos+1]) &0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      if (pos > start && preTokens[pos] == PRE_AND && pos < end) {
        if (preTokens[pos-1] < 0x80000000 && preTokens[pos+1] < 0x80000000) {
          preTokens[pos-1] = (preTokens[pos-1] & preTokens[pos+1]) &0xffff;
          for (i=pos; i<end-1; i++) preTokens[i] = preTokens[i+2];
          end -= 2;
          preTokenCount -= 2;
          flag = -1;
          pos--;
          }
        }
      pos++;
      }

    }
  }

int preIf(char* line) {
  preTokenize(line);
  preReduce(0,preTokenCount-1);
  if (preTokenCount == 0) return 0;
  if (preTokenCount == 1) return preTokens[0];
  showError("Expression error in #if");
  return 0;
  }

