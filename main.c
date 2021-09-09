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

int main() 
{
    // atribuiçao de variaveis
    //
    WBRating* VSB_rating; // vetor de strings pela nota
    MAN_String* vector_string; // vetor de strings tratadas
    int FLAG_GEN_FILE, FLAG_READ_FILE, MAX_LEN_VECTOR, LEN_QUEUE;
    VSB_rating = NULL;
    vector_string = NULL;
    char *file_name_tmp = "Nota1.txt";
    char *pword; // ponteiro para palavras recebidas da leitura do arquivo
    FILE* pFileName = NULL; 
    char opt = '0'; // opção do menu
    MAX_LEN_VECTOR = 0; // tamanho maximo do meu vetor inicia em 0
    LEN_QUEUE = 0; // tamanho do vetor de retorno tratadas

    // Alocação 
    
    VSB_rating = (WBRating*)calloc(5,sizeof(WBRating));
   
    while(opt != 'S'){

        //printf("\n################## CSV PARSER ##################");
        //printf("\n");
        //printf("\nG - Gerar Arquivos de Por Nota de Avaliação");
        //printf("\nC - Criar Vetores com Palavras Únicas");
        //printf("\nM - Mostrar Palavras dos Vetores e Respctivas Ocorrencias");
        //printf("\nE - Exibir o Numero de Palavras de Cada Arquivo de Avaliação");
        //printf("\nS - Sair");
        //printf("\nOpção: ");
        scanf("\n%c", &opt);
        
        switch(opt){

            case 'G':
                
                printf("Essa Opção irá apagar o arquivos de Avaliação caso eles já existão,\n(OBS: apagar os arquivos e reescreve-los pode afetar a integridade\ndo funcionamento do programa.\nDeseja continuar? [Y/N:])");
                setbuf(stdin,NULL);
                char opt_tmp;
                scanf("%c",&opt_tmp);
                if(opt_tmp == 'Y' || opt_tmp == 'y'){
                    printf("\n");
                    if(GenFiles(pFileName))
                        fclose(pFileName);
                    else
                        printf("Arquivos Gerados com Sucesso!\n");
                }
                else
                    continue;
            case 'C':

                pFileName = OpenFileRead(file_name_tmp);    
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
                    
            case 'S':
                break;
                
        }
    }
    
    //pFileName = OpenFileRead(file_name_tmp);    
    //while(1)
    //{
    //    FLAG_READ_FILE = ReadFile(pFileName,pword);
    //    if(feof(pFileName))
    //        break;
    //    else{
    //        vector_string = SplitWords(vector_string,pword,&LEN_QUEUE);
    //        for(int i = 0; i <= LEN_QUEUE; i++){
    //            VSB_rating[0].LEN_WORD_TEXT++;
    //            if(strlen(vector_string[i].word) > 3)
    //                VSB_rating[0].words = InsertSort(VSB_rating[0].words, &VSB_rating[0].len_vetctor, vector_string[i].word);   
    //            else
    //                continue;
    //            }
    //            LEN_QUEUE = 0;
    //        }
    //}
    //fclose(pFileName);
    for(int i = 0; i < VSB_rating[0].len_vetctor; i++){
        printf("palavra: %s  |  numero de vezes: %i\n",VSB_rating[0].words[i].word, VSB_rating[0].words[i].num);
    }
    printf("%i\n%i\n",VSB_rating[0].len_vetctor,VSB_rating[0].LEN_WORD_TEXT);
    FreeVector(VSB_rating[0].words,VSB_rating[0].len_vetctor); 
    return 0;
}
