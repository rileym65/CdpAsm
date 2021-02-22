#include "header.h"

char* mystrstr(char* line, char* what) {
  char* pchar;
  pchar = strstr(line, what);
  if (pchar == NULL) return NULL;
  if (pchar > line) {
    if (*(pchar-1) >= 'a' && *(pchar-1) <= 'z') return NULL;
    if (*(pchar-1) >= 'A' && *(pchar-1) <= 'Z') return NULL;
    }
  if (*(pchar+strlen(what)) >= 'a' && *(pchar+strlen(what)) <= 'z') return NULL;
  if (*(pchar+strlen(what)) >= 'A' && *(pchar+strlen(what)) <= 'Z') return NULL;
  if (*(pchar+strlen(what)) >= '0' && *(pchar+strlen(what)) <= '9') return NULL;
  return pchar;
  }

int readLine() {
  int   i;
  int   count;
  char *pchar;
  char op[256];
  char args[256];
  char trans[256];
  char temp[2048];
  if (readFile() == 0) return 0;

  /* ************************** */
  /* ***** Process #endif ***** */
  /* ************************** */
  if (strncmp(line,"#endif",6) == 0) {
    strcpy(line,"");
    return -1;
    }

  /* ************************* */
  /* ***** Process #else ***** */
  /* ************************* */
  if (strncmp(line, "#else", 5) == 0) {
    count = 1;
    while (count > 0) {
      if (readFile() == 0) {
        showError("Unexpected end of file");
        exit(1);
        }
      if (strncmp(line, "#if", 3) == 0) count++;
      if (strncmp(line, "#endif", 6) == 0) count--;
      }
      strcpy(line,"");
      return -1;
    }

  /* *********************** */
  /* ***** Process #if ***** */
  /* *********************** */
  if (strncmp(line,"#if ",4) == 0) {
    if (preIf(line+4)) {
      strcpy(line,"");
      return -1;
      }
    else {
      if (pass == 2 && showList) {
        if (currentFile == 0) printf("[%05d]                   %s\n",lineNumber,line);
        else printf("<%05d>                   %s\n",lineNumber,line);
        }
      count = 1;
      while (count > 0) {
        if (readFile() == 0) {
          showError("Unexpected end of file");
          exit(1);
          }
        if (strncmp(line, "#if", 3) == 0) count++;
        if (strncmp(line, "#endif", 6) == 0) count--;
        if (strncmp(line, "#else", 5) == 0) count--;
        }
      strcpy(line,"");
      return -1;
      }

    }

  /* ************************** */
  /* ***** Process #ifdef ***** */
  /* ************************** */
  if (strncmp(line,"#ifdef",6) == 0) {
    pchar = line+6;
    while (*pchar == ' ' || *pchar == '\t') pchar++;
    if (*pchar == 0) {
      showError("Invalid #ifdef");
      strcpy(line,"");
      return -1;
      }
    i = 0;
    while (*pchar != ' ' && *pchar != '\t' && *pchar != 0) op[i++] = *pchar++;
    op[i] = 0;
    if (findDefine(op) >= 0) {
      strcpy(line,"");
      return -1;
      }
    else {
      if (pass == 2 && showList) {
        if (currentFile == 0) printf("[%05d]                   %s\n",lineNumber,line);
        else printf("<%05d>                   %s\n",lineNumber,line);
        }
      count = 1;
      while (count > 0) {
        if (readFile() == 0) {
          showError("Unexpected end of file");
          exit(1);
          }
        if (strncmp(line, "#if", 3) == 0) count++;
        if (strncmp(line, "#endif", 6) == 0) count--;
        if (strncmp(line, "#else", 5) == 0) count--;
        }
      strcpy(line,"");
      return -1;
      }
    }

  /* *************************** */
  /* ***** Process #ifndef ***** */
  /* *************************** */
  if (strncmp(line,"#ifndef",7) == 0) {
    pchar = line+7;
    while (*pchar == ' ' || *pchar == '\t') pchar++;
    if (*pchar == 0) {
      showError("Invalid #ifdef");
      strcpy(line,"");
      return -1;
      }
    i = 0;
    while (*pchar != ' ' && *pchar != '\t' && *pchar != 0) op[i++] = *pchar++;
    op[i] = 0;
    if (findDefine(op) < 0) {
      strcpy(line,"");
      return -1;
      }
    else {
      if (pass == 2 && showList) {
        if (currentFile == 0) printf("[%05d]                   %s\n",lineNumber,line);
        else printf("<%05d>                   %s\n",lineNumber,line);
        }
      count = 1;
      while (count > 0) {
        if (readFile() == 0) {
          showError("Unexpected end of file");
          exit(1);
          }
        if (strncmp(line, "#if", 3) == 0) count++;
        if (strncmp(line, "#endif", 6) == 0) count--;
        if (strncmp(line, "#else", 5) == 0) count--;
        }
      strcpy(line,"");
      return -1;
      }
    }

  /* *************************** */
  /* ***** Process #define ***** */
  /* *************************** */
  if (strncmp(line,"#define",7) == 0) {
    pchar = line+7;
    while (*pchar == ' ' || *pchar == '\t') pchar++;
    if (*pchar == 0) {
      showError("Invalid #define");
      strcpy(line,"");
      return -1;
      }
    i = 0;
    while (*pchar != ' ' && *pchar != '\t' && *pchar != 0) op[i++] = *pchar++;
    op[i] = 0;
    while (*pchar == ' ' || *pchar == '\t') pchar++;
    if (*pchar == 0 || *pchar == ';') {
      addDefine(op,"1");
      strcpy(line,"");
      return -1;
      }
    i = 0;
    while (*pchar != 0 && *pchar != ';') args[i++] = *pchar++;
    args[i] = 0;
    i = strlen(args);
    while (i > 0 && (args[i-1] == ' ' || args[i-1] == '\t')) {
      args[i-1] = 0;
      i--;
      }
    addDefine(op,args);
    strcpy(line,"");
    return -1;
    }

  /* ************************** */
  /* ***** Process #undef ***** */
  /* ************************** */
  if (strncmp(line,"#undef",6) == 0) {
    pchar = line+6;
    while (*pchar == ' ' || *pchar == '\t') pchar++;
    if (*pchar == 0) {
      showError("Invalid #undef");
      strcpy(line,"");
      return -1;
      }
    i = 0;
    while (*pchar != ' ' && *pchar != '\t' && *pchar != 0) op[i++] = *pchar++;
    op[i] = 0;
    undef(op);
    strcpy(line,"");
    return -1;
    }

  /* ************************* */
  /* ***** Process .1805 ***** */
  /* ************************* */
  if (strncasecmp(line,".1805a",6) == 0) {
    if (pass == 1) setup1805(1);
    strcpy(line,"");
    }
  else if (strncasecmp(line,".1805",5) == 0) {
    if (pass == 1) setup1805(0);
    strcpy(line,"");
    }

  /* ************************* */
  /* ***** Process .list ***** */
  /* ************************* */
  if (strncasecmp(line,".list",5) == 0) {
    showList = -1;
    strcpy(line,"");
    }

  /* ************************* */
  /* ***** Process .xref ***** */
  /* ************************* */
  if (strncasecmp(line,".xref",5) == 0) {
    showXref = -1;
    strcpy(line,"");
    }

  /* *************************** */
  /* ***** Process include ***** */
  /* *************************** */
  if (strncasecmp(line,"include",7) == 0) {
    pchar = line+7;
    while (*pchar == ' ' || *pchar == '\t') pchar++;
    currentFile++;
    files[currentFile] = fopen(pchar,"r");
    if (files[currentFile] == NULL) {
      printf("Could not open included file: %s\n",pchar);
      exit(1);
      }
    lineNumbers[lineNumberSP++] = lineNumber;
    lineNumber = 0;
    strcpy(line,"");
    }

  /* *********************** */
  /* ***** Process .op ***** */
  /* *********************** */
  if (strncasecmp(line,".op",3) == 0) {
    if (pass == 1) {
      pchar = line+3;
      while (*pchar == ' ' || *pchar == '\t') pchar++;
      if (*pchar != '"') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      i = 0;
      while (*pchar != '"' && *pchar != 0) op[i++] = *pchar++;
      op[i] = 0;
      if (*pchar != '"') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      while (*pchar != ',' && *pchar != 0) pchar++;
      if (*pchar != ',') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      while (*pchar != '"' && *pchar != 0) pchar++;
      if (*pchar != '"') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      i = 0;
      while (*pchar != '"' && *pchar != 0) args[i++] = *pchar++;
      args[i] = 0;
      if (*pchar != '"') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      while (*pchar != ',' && *pchar != 0) pchar++;
      if (*pchar != ',') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      while (*pchar != '"' && *pchar != 0) pchar++;
      if (*pchar != '"') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      pchar++;
      i = 0;
      while (*pchar != '"' && *pchar != 0) trans[i++] = *pchar++;
      trans[i] = 0;
      if (*pchar != '"') {
        showError("Syntax error in .op");
        strcpy(line,"");
        return -1;
        }
      opcode(op, args, trans);
      strcpy(line,"");
      }
    strcpy(line,"");
    }
  for (i=0; i<defineCount; i++) {
    while ((pchar = mystrstr(line, defines[i])) != NULL) {
      strncpy(temp, line, pchar-line);
      temp[pchar-line] = 0;
      strcat(temp, defineValues[i]);
      strcat(temp,pchar+strlen(defines[i]));
      strcpy(line,temp);
      }
    }
  return -1;
  }
