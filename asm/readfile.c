#include "header.h"

int readFile() {
  strcpy(line,"");
  while (currentFile >= 0 && feof(files[currentFile])) {
    fclose(files[currentFile]);
    currentFile--;
    if (lineNumberSP > 0) {
      lineNumberSP--;
      lineNumber = lineNumbers[lineNumberSP];
      }
    }
  if (currentFile < 0) return 0;
  fgets(line,1023,files[currentFile]);
  while (strlen(line) > 0 && (line[strlen(line)-1] == 10 || line[strlen(line)-1] == 13))
    line[strlen(line)-1] = 0;
  lineNumber++;
  linesRead++;
  strcpy(rawLine, line);
  return -1;
  }
