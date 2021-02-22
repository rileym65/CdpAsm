#define MAIN
#include "header.h"

void assembleFile(char* sourceName) {
  int i;
  int j;

  numOpcodes = 0;
  labelCount = 0;
  defineCount = 0;
  publicsCount = 0;
  setup();
  errors = 0;
  currentFile = 0;
  startAddress = 0;

  strcpy(baseName, sourceName);
  if (strchr(baseName,'.') != NULL) {
    *(strchr(baseName,'.')) = 0;
    }
  strcpy(destName,baseName);
  strcat(destName,".prg");
  if (strchr(sourceName,'.') == NULL)
    strcat(sourceName,".asm");

  printf("Assembling: %s\n",sourceName);

  files[0] = fopen(sourceName,"r");
  assemblyPass(1);
  while (currentFile >= 0) {
    fclose(files[0]);
    currentFile--;
    }
  currentFile = 0;
  files[0] = fopen(sourceName,"r");
  outFile = fopen(destName,"w");
  outCount = 0;
  assemblyPass(2);
  flush();
  fprintf(outFile,"*%04x\n",startAddress);
  for (i=0; i<publicsCount; i++)
    fprintf(outFile,"=%04x %s\n",lookupLabel(publics[i]),publics[i]);
  fclose(outFile);
  while (currentFile >= 0) {
    fclose(files[0]);
    currentFile--;
    }

  if (showXref) {
    printf("\n");
    for (i=0; i<labelCount; i++) {
      if (labelFlags[i] & LFLAGS_EXTERN) printf("*"); else printf(" ");
     
      printf(" %04x: %-20s - <%5d>",labelValues[i], labels[i], labelLine[i]);
      for (j=0; j<labelUsedCount[i]; j++) printf(" %5d",labelUsed[i][j]);
      printf("\n");
      }
    }

  if (verbose) {
    printf("\nPublic Symbols:\n");
    for (i=0; i<publicsCount; i++) {
      printf("  %-20s  %04x\n",publics[i],lookupLabel(publics[i]));
      }
    printf("\nDefines:\n");
    for (i=0; i<defineCount; i++) {
      printf("  %-20s  %s\n",defines[i],defineValues[i]);
      }
    printf("\n");
    printf("Lowest address  : %04x\n",lowest);
    printf("Highest address : %04x\n",highest);
    }

  printf("\n");
  printf("Lines Assembled: %d\n",linesRead);
  printf("Errors         : %d\n",errors);
  printf("Code Generated : %d\n",codeGenerated);
  printf("\n");

  if (defineCount > 0) {
    for (i=0; i<defineCount; i++) {
      free(defineValues[i]);
      free(defines[i]);
      }
    free(defineValues);
    free(defines);
    }

  if (publicsCount > 0) {
    for (i=0; i<publicsCount; i++)
      free(publics[i]);
    free(publics);
    }

  if (labelCount > 0) {
    for (i=0; i<labelCount; i++) {
      free(labels[i]);
      if (labelUsedCount[i] > 0) {
        free(labelUsed[i]);
        }
      }
    free(labels);
    free(labelValues);
    free(labelFlags);
    free(labelLine);
    free(labelUsed);
    }
  }

int main(int argc, char** argv) {
  int i;

  showList = 0;
  verbose = 0;
  numSourceFiles = 0;
  
  strcpy(sourceName,"");
  for (i=1; i<argc; i++) {
    if (strcmp(argv[i],"-l") == 0) showList = -1;
    if (strcmp(argv[i],"-x") == 0) showXref = -1;
    if (strcmp(argv[i],"-v") == 0) verbose = -1;
    if (strcmp(argv[i],"-V") == 0) printf("Cdp/Asm v%s\n",VERSION);
    if (strncmp(argv[i],"-D",2) == 0) {
      addDefine(argv[i]+2,"1");
      }
    if (argv[i][0] != '-') {
      if (numSourceFiles == 0)
        sourceFiles = (char**)malloc(sizeof(char*));
      else
        sourceFiles = (char**)realloc(sourceFiles,sizeof(char*)*(numSourceFiles+1));
      sourceFiles[numSourceFiles] = (char*)malloc(strlen(argv[i])+1);
      strcpy(sourceFiles[numSourceFiles++], argv[i]);
      } 
    }
  if (numSourceFiles == 0) {
    printf("No source files\n");
    exit(1);
    }

  for (i=0; i<numSourceFiles; i++) {
    assembleFile(sourceFiles[0]);
    }

  return 0;
  }


