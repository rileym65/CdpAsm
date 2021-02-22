#include "header.h"

void reduce(int start, int end) {
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
        if ((tokens[pos] & FLG_OP) && ((tokens[pos] & 0xffff) == '(')) op = pos;
        if ((tokens[pos] & FLG_OP) && ((tokens[pos] & 0xffff) == ')')) {
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
        for (i=op; i<numTokens-1; i++) tokens[i] = tokens[i+1];
        end--;
        numTokens--;
        cp--;
        for (i=cp; i<numTokens-1; i++) tokens[i] = tokens[i+1];
        end--;
        numTokens--;
        cp--;
        reduce(op,cp);
        end = numTokens - 1;
        pflag = -1;
        }
      }

    /* ********************************* */
    /* ***** Check for high, low   ***** */
    /* ********************************* */
    pos = start;
    while (pos <= end) {
      if (tokens[pos] & FLG_OP) {
        if ((tokens[pos] & 0xffff) == 'H') {
          tokens[pos+1] = (tokens[pos+1] & 0xffff0000) |
                          ((tokens[pos+1] & 0xff00) >> 8);
          for (i=pos; i<numTokens-1; i++) tokens[i] = tokens[i+1];
          end -= 1;
          numTokens -= 1;
          flag = -1;
          }
        else if ((tokens[pos] & 0xffff) == 'L') {
          tokens[pos+1] = (tokens[pos+1] & 0xffff0000) |
                          (tokens[pos+1] & 0xff);
          for (i=pos; i<numTokens-1; i++) tokens[i] = tokens[i+1];
          end -= 1;
          numTokens -= 1;
          flag = -1;
          }
        else pos++;
        }
      else pos++;
      }


    /* ********************************* */
    /* ***** Check for .1/.0       ***** */
    /* ********************************* */
    pos = start;
    while (pos <= end) {
      if (tokens[pos] & FLG_OP) {
        if ((tokens[pos] & 0xffff) == '.') {
          if (tokens[pos+1] == 1)
            tokens[pos-1] = (tokens[pos-1] & 0xffff0000) |
                            ((tokens[pos-1] & 0xff00) >> 8);
          else
            tokens[pos-1] = (tokens[pos-1] & 0xffff0000) |
                            (tokens[pos-1] & 0xff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else pos++;
        }
      else pos++;
      }

    /* ********************************* */
    /* ***** Check for *, /        ***** */
    /* ********************************* */
    pos = start;
    while (pos <= end) {
      if (tokens[pos] & FLG_OP) {
        if ((tokens[pos] & 0xffff) == '*') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) * (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else if ((tokens[pos] & 0xffff) == '/') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) / (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else pos++;
        }
      else pos++;
      }

    /* ********************************* */
    /* ***** Check for +, -        ***** */
    /* ********************************* */
    pos = start;
    while (pos <= end) {
      if (tokens[pos] & FLG_OP) {
        if ((tokens[pos] & 0xffff) == '+') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) + (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else if ((tokens[pos] & 0xffff) == '-') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) - (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else pos++;
        }
      else pos++;
      }

    /* ********************************* */
    /* ***** Check for |, &, ^     ***** */
    /* ********************************* */
    pos = start;
    while (pos <= end) {
      if (tokens[pos] & FLG_OP) {
        if ((tokens[pos] & 0xffff) == '|') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) | (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else if ((tokens[pos] & 0xffff) == '&') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) & (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else if ((tokens[pos] & 0xffff) == '^') {
          tokens[pos-1] = ((tokens[pos-1] & 0xffff0000) | (tokens[pos+1] & 0xffff0000)) |
                           (((tokens[pos-1] & 0xffff) ^ (tokens[pos+1] & 0xffff)) & 0xffff);
          for (i=pos; i<numTokens-2; i++) tokens[i] = tokens[i+2];
          end -= 2;
          numTokens -= 2;
          flag = -1;
          }
        else pos++;
        }
      else pos++;
      }

    }
  }
