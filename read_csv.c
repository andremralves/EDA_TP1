#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "read_csv.h"
#define LENBUFF 5000
#define LEN_STR_FILE 40

FILE* Open_file_read(char* pFileName){
    return fopen(pFileName,"r"); // abre arquivo para leitura
}

FILE* Open_file_write(char* pFileName){
    return fopen(pFileName,"a"); // abri arquivo para escrita no final do arquivo
}

bool Separa_por_nota(FILE* File_csv){
        
    if(File_csv == NULL){
        printf("Arquivo não encontrado!\n");
        return false;
    }
    
    char buff[LENBUFF], *Text,*auxText, Rating;
    auxText = (char*)malloc(sizeof(char)*sizeof(buff));
    Text = (char*)malloc(sizeof(char)*sizeof(buff));
    int col_cont = 0;
    bool sep_flag = false;

    while(fgets(buff,LENBUFF,File_csv)){
        auxText = strtok(buff,"\"");
        col_cont = 0;
            
        while(auxText){
            if(col_cont == 0)
                Text = auxText;

            if(col_cont == 1){
                Rating = auxText[1];
                sep_flag = Write_txt_files(Text,Rating);
            }
            
            auxText = strtok(NULL,"\"");
            col_cont++;    
        }
    }
    fclose(File_csv);
    free(auxText);
    return true;
}

bool Write_txt_files(char* Text, char Num_file){
    char file_txt_name[9] = {"Nota*.txt"};
    file_txt_name[4] = Num_file;
    char * Insert_Text;
    FILE* pTxtFiles;
    pTxtFiles = Open_file_write(file_txt_name);
    
    fprintf(pTxtFiles,"%s\n",Text);
    //fwrite(Text,sizeof(char),strlen(Text),pTxtFiles);
    fclose(pTxtFiles);
    return true;
}

int ReadFile(FILE* file_name, char* pword){    
    if(fscanf(file_name,"%s",pword) < 1)
        return 0;
    return 1;
}
