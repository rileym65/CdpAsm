#include "header.h"

word fromHex(char* num) {
  word ret;
  ret = 0;
  while ((*num >= '0' && *num <= '9') ||
         (*num >= 'a' && *num <= 'f') ||
         (*num >= 'A' && *num <= 'F')) {
    ret <<= 4;
    if (*num >= '0' && *num <= '9') ret |= (*num - '0');
    if (*num >= 'a' && *num <= 'f') ret |= ((*num - 'a') + 10);
    if (*num >= 'A' && *num <= 'F') ret |= ((*num - 'A') + 10);
    num++;
    }
  return ret;
  }
