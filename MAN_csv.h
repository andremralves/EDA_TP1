#ifndef MAN_CSV_H
#define MAN_CSV_H
#include <stdbool.h>
#include <stdio.h>

FILE* OpenFileRead(char* FileName);
FILE* OpenFileWrite(char* FileName);
int ReadFile(FILE *file_name, char* pword);
bool WriteTxtFiles(char* Text, char Num_file);
bool SplitByRate(FILE *Arquivo_csv);
int GenFiles(FILE* pFileName);
void DelFiles();
#endif

