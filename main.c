#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "read_csv.h"
#include "gen_vector.h"
#include "string_manipulation.h"
#define LEN_STR_FILE 40


int main() {

//    scanf("%s",nomearquivo);
//    FILE* pFileName = Open_file_read(nomearquivo);
//    bool flag = Separa_por_nota(pFileName); 
    
    Word* words;
    char* file_name = "teste.txt";
    char* pword;
    int flag, max_len_vetor = 0, lenvet = 0;
    MAN_String* vector_string;
    
    FILE* pFileName = Open_file_read(file_name);
    while(1)
    {
        flag = ReadFile(pFileName,pword);
        if(feof(pFileName))
            break;
        else{
            vector_string = SplitWords(vector_string,pword,&lenvet);
            for(int i = 0; i <= lenvet; i++){
                if(strlen(vector_string[i].word) > 3) 
                    words = InsertSort(words, &max_len_vetor,vector_string[i].word);   
                else
                    continue;
            }
            lenvet = 0;
        }
    }

    for(int i = 0; i < max_len_vetor; i++){
        printf("palavra: %s  |  numero de vezes: %i\n",words[i].word, words[i].num);
    }
    return 0;
}
