#include "header.h"

int isRReg(char* msg) {
  int ret;
  if (*msg != 'R' && *msg != 'r') return -1;
  msg++;
  if (*msg >= '0' && *msg <= '9') {
    ret = *msg - '0';
    msg ++;
    if (*msg >= 'a' && *msg <= 'z') return -1;
    if (*msg >= 'A' && *msg <= 'Z') return -1;
    if (*msg >= '0' && *msg <= '9') {
      ret *= 10;
      ret += (*msg - '0');
      if (ret > 15) return -1;
      msg++;
      if (*msg >= 'a' && *msg <= 'z') return -1;
      if (*msg >= 'A' && *msg <= 'Z') return -1;
      if (*msg >= '0' && *msg <= '9') return -1;
      return ret;
      }
    return ret;
    }
  if ((*msg >= 'a' && *msg <= 'f') ||
      (*msg >= 'A' && *msg <= 'F')) {
    if (*msg >= 'a' && *msg <= 'f') ret = *msg - 'a' + 10;
    if (*msg >= 'A' && *msg <= 'F') ret = *msg - 'A' + 10;
    msg++;
    if (*msg >= '0' && *msg <= '9') return -1;
    if (*msg >= 'a' && *msg <= 'z') return -1;
    if (*msg >= 'A' && *msg <= 'Z') return -1;
    if (*msg == '_') return -1;
    return ret;
    }
  return -1;
  }
