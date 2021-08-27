#ifndef READ_CSV_H
#define READ_CSV_H
#include <stdbool.h>
#include <stdio.h>

FILE* Open_file_read(char* FileName);
FILE* Open_file_write(char* FileName);
bool Write_txt_files(char* Text, char Num_file);
bool Separa_por_nota(FILE *Arquivo_csv);

#endif

