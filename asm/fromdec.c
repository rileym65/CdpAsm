#include "header.h"

word fromDec(char* num) {
  word ret;
  ret = 0;
  while (*num >= '0' && *num <= '9') {
    ret *= 10;
    ret += (*num - '0');
    num++;
    }
  return ret;
  }
