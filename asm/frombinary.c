#include "header.h"

word fromBinary(char* num) {
  word ret;
  ret = 0;
  while (*num >= '0' && *num <= '1') {
    ret <<= 1;
    if (*num == '1') ret |= 1;
    num++;
    }
  return ret;
  }
