#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "read_csv.h"
#include "gen_vector.h"
#define LEN_STR_FILE 40


int main() {
    char nomearquivo[LEN_STR_FILE];
    scanf("%s",nomearquivo);
    FILE* pFileName = Open_file_read(nomearquivo);
    bool flag = Separa_por_nota(pFileName); 
    
    Word* words;
    char* file_name = "teste.txt";
    char* pword;
    int flag, max_len_vetor = 0;
    FILE* pFileName = Open_file_read(file_name);
    while(1)
    {
        flag = ReadFile(pFileName,pword);
        if(feof(pFileName))
            break;
        else
            if(strlen(pword) > 3) 
                words = InsertSort(words, &max_len_vetor,pword);   
    }

    for(int i = 0; i < max_len_vetor; i++){
        printf("palavra: %s  |  numero de vezes: %i\n",words[i].word, words[i].num);
    }
    return 0;
    
}
