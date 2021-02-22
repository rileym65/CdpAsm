#include "header.h"

int loadFile(int index) {
  int   i;
  int   j;
  int   valid;
  word  address;
  word  value;
  FILE* infile;
  char  line[1024];
  char  symbol[128];
  address = 0;
  if (verbose)
    printf("Loading file: %s\n",files[index]);
  infile = fopen(files[index],"r");
  if (infile == NULL) {
    printf("Could not open object file: %s\n",files[index]);
    return 0;
    }
  while (fgets(line, 1023, infile) != NULL) {
    for (i=0; i<strlen(line); i++)
      if (line[i] < ' ') line[i] = 0;
    /* ************************** */
    /* ***** Load data line ***** */
    /* ************************** */
    if (line[0] == ':') {
      i=1;
      address = 0;
      while (line[i] != 0 && line[i] != ' ') {
        address <<= 4;
        if (line[i] >= '0' && line[i] <= '9') address |= (line[i] - '0');
        if (line[i] >= 'a' && line[i] <= 'f') address |= ((line[i] - 'a' + 10));
        if (line[i] >= 'A' && line[i] <= 'F') address |= ((line[i] - 'a' + 10));
        i++;
        }
      valid = 0;
      value = 0;
      while (line[i] != 0) {
        while (line[i] == ' ') i++;
        while ((line[i] >= '0' && line[i] <= '9') ||
               (line[i] >= 'a' && line[i] <= 'f') ||
               (line[i] >= 'A' && line[i] <= 'F')) {
          value <<= 4;
          if (line[i] >= '0' && line[i] <= '9') value |= (line[i] - '0');
          if (line[i] >= 'a' && line[i] <= 'f') value |= ((line[i] - 'a' + 10));
          if (line[i] >= 'A' && line[i] <= 'F') value |= ((line[i] - 'a' + 10));
          valid = -1;
          i++;
          }
        if (valid) {
          if (used[address] != 0) {
            printf("Error: Memory overlap: %04x\n",address);
            errors++;
            }
          if (address > highest) highest = address;
          if (address < lowest) lowest = address;
          used[address] = 1;
          memory[address++] = value;
          value = 0;
          valid = 0;
          }
        }
      if (valid) {
        if (used[address] != 0) {
          printf("Error: Memory overlap: %04x\n",address);
          errors++;
          }
        if (address > highest) highest = address;
        if (address < lowest) lowest = address;
        used[address] = 1;
        memory[address++] = value;
        value = 0;
        valid = 0;
        }
      }

    /* ******************************** */
    /* ***** Process exec address ***** */
    /* ******************************** */
    else if (line[0] == '*') {
      i=1;
      execAddress = 0;
      while (line[i] != 0 && line[i] != ' ') {
        execAddress <<= 4;
        if (line[i] >= '0' && line[i] <= '9') execAddress |= (line[i] - '0');
        if (line[i] >= 'a' && line[i] <= 'f') execAddress |= ((line[i] - 'a' + 10));
        if (line[i] >= 'A' && line[i] <= 'F') execAddress |= ((line[i] - 'a' + 10));
        i++;
        }
      }

    /* ********************************* */
    /* ***** Process public symbol ***** */
    /* ********************************* */
    else if (line[0] == '=') {
      i=1;
      value = 0;
      while (line[i] != 0 && line[i] != ' ') {
        value <<= 4;
        if (line[i] >= '0' && line[i] <= '9') value |= (line[i] - '0');
        if (line[i] >= 'a' && line[i] <= 'f') value |= ((line[i] - 'a' + 10));
        if (line[i] >= 'A' && line[i] <= 'F') value |= ((line[i] - 'a' + 10));
        i++;
        }
      while (line[i] == ' ') i++;
      if (line[i] == 0) {
        printf("Error: Invalid public symbol definition\n");
        errors++;
        }
      else {
        j = 0;
        while (line[i] > ' ') {
          symbol[j++] = line[i++];
          }
        symbol[j] = 0;
        addSymbol(symbol, value, files[index]);
        }
      }

    else {
      printf("Warning: Unknown line ignored: %s\n",line);
      }
    }

  fclose(infile);
  return -1;
  }

