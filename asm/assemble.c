#include "header.h"

int assemble(char* line) {
  int i;
  byte v;
  int  valid;
  int  pos;
  int  j;
  int  k;
  char buildName[1024];
  FILE* buildFile;
  char  buffer[100];
  struct tm      t;
  time_t         seconds;
  char tmp[256];
  parse(line);
  if (strlen(label) == 0 && strlen(op) == 0) {
    if (pass == 2 && showList) {
      if (lineNumberSP == 0)
        printf("[%05d]                   %s\n",lineNumber,rawLine);
      else
        printf("<%05d>                   %s\n",lineNumber,rawLine);
      }
    return 0;
    }
/*
  printf("%s\n",line);
  printf("  label: %s\n",label);
  printf("  op   : %s\n",op);
  printf("  args : %d\n",argCount);
  for (i=0; i<argCount; i++)
    printf("         %x\n",args[i]);
*/

  if (label[0] != 0 && pass == 1) {
    if (lookupLabel(label) < 0) {
      if (labelCount == 0) {
        labels = (char**)malloc(sizeof(char*));
        labelValues = (UInt32*)malloc(sizeof(UInt32));
        labelFlags = (word*)malloc(sizeof(word));
        labelLine = (UInt32*)malloc(sizeof(UInt32));
        labelUsedCount = (UInt32*)malloc(sizeof(UInt32));
        labelUsed = (UInt32**)malloc(sizeof(UInt32*));
        }
      else {
        labels = (char**)realloc(labels,sizeof(char*) * (labelCount+1));
        labelValues = (UInt32*)realloc(labelValues,sizeof(UInt32) * (labelCount+1));
        labelFlags = (word*)realloc(labelFlags,sizeof(word) * (labelCount+1));
        labelLine = (UInt32*)realloc(labelLine,sizeof(UInt32) * (labelCount+1));
        labelUsedCount = (UInt32*)realloc(labelUsedCount,sizeof(UInt32) * (labelCount+1));
        labelUsed = (UInt32**)realloc(labelUsed,sizeof(UInt32*) * (labelCount+1));
        }
      labelValues[labelCount] = address;
      labels[labelCount] = (char*)malloc(strlen(label)+1);
      strcpy(labels[labelCount],label);
      labelFlags[labelCount] = 0;
      labelLine[labelCount] = lineNumber;
      labelUsedCount[labelCount] = 0;
      labelCount++;
      }
    else {
      sprintf(tmp,"Label multiply defined: %s",label);
      showError(tmp);
      }
    }
  curAddress = address;
  numCodes = 0;
  i = lookupOpcode();
  if (i<0 && strlen(op) > 0) {
    showError("Invalid opcode");
    printf("       %s",rawLine);
    }
  if (i >= 0) {
    v = 0;
    pos = 0;
    valid = 0;
    while (pos < strlen(o_trans[i])) {
      if (o_trans[i][pos] >= '0' && o_trans[i][pos] <= '9') {
        v <<= 4;
        v |= (o_trans[i][pos] - '0');
        valid = 1;
        }
      else if (o_trans[i][pos] >= 'a' && o_trans[i][pos] <= 'f') {
        v <<= 4;
        v |= (o_trans[i][pos] - 'a' + 10);
        valid = 1;
        }
      else if (o_trans[i][pos] >= 'A' && o_trans[i][pos] <= 'F') {
        v <<= 4;
        v |= (o_trans[i][pos] - 'A' + 10);
        valid = 1;
        }
      else if (o_trans[i][pos] == '|') {
        pos++;
        j = o_trans[i][pos] - '1';
        v |= args[j];
        valid = 1;
        }
      else if (o_trans[i][pos] == '/') {
        pos++;
        v <<= 4;
        j = o_trans[i][pos] - '1';
        v |= args[j];
        valid = 1;
        }
      else if (o_trans[i][pos] == 'h' &&
               o_trans[i][pos+1] == 'i' &&
               o_trans[i][pos+2] == '(' &&
               o_trans[i][pos+4] == ')') {
        j = o_trans[i][pos+3] - '1';
        v = (args[j] & 0xff00) >> 8;
        pos += 4;
        valid = 1;
        }
      else if (o_trans[i][pos] == 'l' &&
               o_trans[i][pos+1] == 'o' &&
               o_trans[i][pos+2] == '(' &&
               o_trans[i][pos+4] == ')') {
        j = o_trans[i][pos+3] - '1';
        v = args[j] & 0xff;
        pos += 4;
        valid = 1;
        }
      else if (o_trans[i][pos] == '*') {
        j = 0;
        valid = 0;
        while (o_trans[i][pos] != 0) tmp[j++] = o_trans[i][pos++];
        tmp[j] = 0;
        if (strcasecmp(tmp,"*org") == 0) {
          if (pass == 2 && showList) {
            if (lineNumberSP == 0)
              printf("[%05d]       *%04x       %s",lineNumber,args[0] & 0xffff,line);
            else
              printf("<%05d>       *%04x       %s",lineNumber,args[0] & 0xffff,line);
            }
          address = args[0] & 0xffff;
          flush();
          }
        if (strcasecmp(tmp,"*equ") == 0) {
          if (pass == 2 && showList) {
            if (lineNumberSP == 0)
              printf("[%05d]       =%04x       %s",lineNumber,args[0] & 0xffff,line);
            else
              printf("<%05d>       =%04x       %s",lineNumber,args[0] & 0xffff,line);
            }
          j = findLabel(label);
          if (j >= 0) labelValues[j] = args[0] & 0xffff;
          }
        if (strcasecmp(tmp,"*extern") == 0) {
          if (pass == 2 && showList) {
            if (lineNumberSP == 0)
              printf("[%05d]                   %s",lineNumber,line);
            else
              printf("<%05d>                   %s",lineNumber,line);
            }
          j = findLabel(label);
          if (j >= 0) {
            labelValues[j] = 0x0000;
            labelFlags[j] |= LFLAGS_EXTERN;
            }
          }
        if (strcasecmp(tmp,"*end") == 0) {
          if (pass == 2 && showList) {
            if (lineNumberSP == 0)
              printf("[%05d]       @%04x       %s",lineNumber,args[0] & 0xffff,line);
            else
              printf("<%05d>       @%04x       %s",lineNumber,args[0] & 0xffff,line);
            }
          startAddress = args[0] & 0xffff;
          }
        if (strcasecmp(tmp,"*db") == 0) {
          for (k=0; k<argCount; k++) output(args[k] & 0xff);
          }
        if (strcasecmp(tmp,"*dw") == 0) {
          for (k=0; k<argCount; k++) {
            output((args[k] & 0xff00) >> 8);
            output(args[k] & 0xff);
            }
          }
        if (strcasecmp(tmp,"*ds") == 0) {
          if (pass == 2 && showList) {
            if (lineNumberSP == 0)
              printf("[%05d] %04x  +%04x       %s",lineNumber,address,args[0],line);
            else
              printf("<%05d> %04x  +%04x       %s",lineNumber,address,args[0],line);
            }
          address += args[0];
          flush();
          }
        if (strcasecmp(tmp,"*exec") == 0) {
          output((args[0] & 0xff00) >> 8);
          output(args[0] & 0xff);
          output(((args[1] - args[0]) & 0xff00) >> 8);
          output((args[1] - args[0]) & 0xff);
          output((args[2] & 0xff00) >> 8);
          output(args[2] & 0xff);
          }
        if (strcasecmp(tmp,"*id") == 0) {
          seconds = time(NULL);
          localtime_r(&seconds, &t);
          output(0x30);
          output(args[0] & 0xff);
          output(t.tm_mon+0x81);
          output(t.tm_mday);
          output(((t.tm_year+1900) & 0xff00) >> 8);
          output((t.tm_year+1900) & 0xff);
          if (pass == 2) {
            strcpy(buildName,baseName);
            strcat(buildName,".num");
            buildFile = fopen(buildName,"r");
            if (buildFile != NULL) {
              fgets(buffer,99,buildFile);
              j = atoi(buffer) + 1;
              fclose(buildFile);
              }
            else {
              j = 1;
              }
            output((j & 0xff00) >> 8);
            output(j & 0xff);
            buildFile = fopen(buildName,"w");
            fprintf(buildFile,"%d\n",j);
            fclose(buildFile);
            }
          else {
            output(0);
            output(0);
            }
          pos--;
          }
        if (strcasecmp(tmp,"*public") == 0) {
          if (pass == 2 && showList) {
            if (lineNumberSP == 0)
              printf("[%05d]                   %s",lineNumber,line);
            else
              printf("<%05d>                   %s",lineNumber,line);
            }
          if (pass == 2) {
            if (publicsCount == 0)
              publics = (char**)malloc(sizeof(char*));
            else
              publics = (char**)realloc(publics,sizeof(char*) * (publicsCount+1));
            publics[publicsCount] = (char*)malloc(strlen(argsAscii[0])+1);
            strcpy(publics[publicsCount++], argsAscii[0]);
            }
          }
        }
      else if (o_trans[i][pos] == ' ' && valid == 1) {
        output(v);
        valid = 0;
        v = 0;
        }
      pos++;
      }
    if (valid) {
      output(v);
      v = 0;
      }
    }
  if (pass == 2 && numCodes > 0 && showList) {
    k = 0;
    v = numCodes;
    if (lineNumberSP == 0) printf("[%05d] %04x: ",lineNumber,curAddress);
      else printf("<%05d> %04x: ",lineNumber,curAddress);
    for (i=0; i<numCodes; i++) {
      printf("%02x ",codes[i]);
      k++;
      if (k == 4) printf("%s",rawLine);
      if (k % 4 == 0 && numCodes > 4) printf("\n              ");
      }
    while (v < 4) {
      printf("   ");
      v++;
      }
    if (numCodes < 4) printf("%s",rawLine);
    }
  if (pass == 2 && showList) printf("\n");
  return 0;
  }
