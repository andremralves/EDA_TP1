#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "read_csv.h"
#include "gen_vector.h"
#include "string_manipulation.h"
#define LEN_STR_FILE 40

int func(){
    


}
int main() {

    Word* words;
    char* pword, *file_name;
    FILE* pFileName; 
    //scanf("%s",file_name);
    //pFileName = Open_file_read(file_name);
    //bool flag = Separa_por_nota(pFileName);  
    
    file_name = "Nota1.txt";
    pFileName = Open_file_read(file_name);
    
    int flag2, max_len_vetor = 0, lenvet = 0, aux = 0;
    MAN_String* vector_string;
    
    while(1)
    {
        flag2 = ReadFile(pFileName,pword);
        if(feof(pFileName))
            break;
        else{
            vector_string = SplitWords(vector_string,pword,&lenvet);
            for(int i = 0; i <= lenvet; i++){
                aux++;
                if(strlen(vector_string[i].word) > 3)
                    words = InsertSort(words, &max_len_vetor,vector_string[i].word);   
                else
                    continue;
            }
            lenvet = 0;
        }
    }
    fclose(pFileName);
    for(int i = 0; i < max_len_vetor; i++){
        printf("palavra: %s  |  numero de vezes: %i\n",words[i].word, words[i].num);
    }
    printf("%i\n%i\n",max_len_vetor,aux);
    FreeVector(words,max_len_vetor); 
    return 0;
}
