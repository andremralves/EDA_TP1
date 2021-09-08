#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MAN_csv.h"
#include "gen_vector.h"
#include "string_manipulation.h"
#define LEN_STR_FILE 40

struct words_by_rating{
    Word* words;
    int len_vetctor;
    int LEN_WORD_TEXT;
};
typedef struct words_by_rating WBRating;

int main() {
    
    // atribuiçao de variaveis
    //
    WBRating* VSB_rating; // vetor de strings pela nota
    MAN_String* vector_string; // vetor de strings tratadas
    int FLAG_GEN_FILE, FLAG_READ_FILE, MAX_LEN_VECTOR, LEN_QUEUE;
    VSB_rating = NULL;
    vector_string = NULL;
    char *pword; // ponteiro para palavras recebidas da leitura do arquivo
    FILE* pFileName = NULL; 
    char *file_name = "Nota1.txt"; // nome generico para Nome de arquivos de texto por nota
    char opt = '0'; // opção do menu
    MAX_LEN_VECTOR = 0; // tamanho maximo do meu vetor inicia em 0
    LEN_QUEUE = 0; // tamanho do vetor de retorno tratadas
    
    // Alocação 
    
    VSB_rating = (WBRating*)calloc(5,sizeof(WBRating));
    //Word* words;
    FLAG_GEN_FILE = GenFiles(pFileName);
    pFileName = OpenFileRead(file_name);
    
    
    while(1)
    {
        FLAG_READ_FILE = ReadFile(pFileName,pword);
        if(feof(pFileName))
            break;
        else{
            vector_string = SplitWords(vector_string,pword,&LEN_QUEUE);
            for(int i = 0; i <= LEN_QUEUE; i++){
                VSB_rating[0].LEN_WORD_TEXT++;
                if(strlen(vector_string[i].word) > 3)
                    VSB_rating[0].words = InsertSort(VSB_rating[0].words, &VSB_rating[0].len_vetctor, vector_string[i].word);   
                else
                    continue;
            }
            LEN_QUEUE = 0;
        }
    }
    fclose(pFileName);
    for(int i = 0; i < VSB_rating[0].len_vetctor; i++){
        printf("palavra: %s  |  numero de vezes: %i\n",VSB_rating[0].words[i].word, VSB_rating[0].words[i].num);
    }
    printf("%i\n%i\n",VSB_rating[0].len_vetctor,VSB_rating[0].LEN_WORD_TEXT);
    FreeVector(VSB_rating[0].words,VSB_rating[0].len_vetctor); 
    return 0;
}
