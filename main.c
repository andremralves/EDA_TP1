#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MAN_csv.h"
#include "gen_vector.h"
#include "string_manipulation.h"
#define LEN_STR_FILE 40

typedef struct words_by_rating WBRating;

int main() 
{
    // atribuiçao de variaveis
    //
    Word** recebe;
    MAN_String* vector_string = NULL; // vetor de strings tratadas
    MAN_String* file_names;
    FILE* pFileName = NULL; 
    char opt = '0'; // opção do menu
    char *pword; // ponteiro para palavras recebidas da leitura do arquivo
    int FLAG_GEN_FILE, FLAG_READ_FILE, LEN_QUEUE;
    int LEN_WORD_TEXT[5] = {0,0,0,0,0};
    int MAX_LEN_VET[5] = {0,0,0,0,0};
    LEN_QUEUE = 0; // tamanho do vetor de retorno tratadas

    // Alocação 
    
    recebe = (Word**)malloc(5*sizeof(Word*));
    
    for(int index = 0; index < 5; index++){
        recebe[index] = (Word*)malloc(1* sizeof(Word));
    }

    file_names = (MAN_String*)malloc(5*sizeof(MAN_String));
    
    file_names[0].word = "Nota1.txt";
    file_names[1].word = "Nota2.txt";
    file_names[2].word = "Nota3.txt";
    file_names[3].word = "Nota4.txt";
    file_names[4].word = "Nota5.txt";

    while(opt != 'S'){

        printf("\n################## CSV PARSER ##################");
        printf("\n");
        printf("\nG - Gerar Arquivos de Por Nota de Avaliação");
        printf("\nC - Criar Vetores com Palavras Únicas");
        printf("\nM - Mostrar Palavras dos Vetores e Respctivas Ocorrencias");
        printf("\nE - Exibir o Numero de Palavras de Cada Arquivo de Avaliação");
        printf("\nS - Sair");
        printf("\nOpção: ");
        scanf("\n%c", &opt);
        
        switch(opt){

            case 'G':

                printf("Essa Opção irá apagar o arquivos de Avaliação caso eles já existão,\n(OBS: apagar os arquivos e reescreve-los pode afetar a integridade\ndo funcionamento do programa.\nDeseja continuar? [Y/N:]");
                setbuf(stdin,NULL);
                char opt_tmp;
                scanf("%c",&opt_tmp);
                if(opt_tmp == 'Y' || opt_tmp == 'y'){
                    DelFiles(); 
                    printf("\n");
                    if(GenFiles(pFileName))
                        fclose(pFileName);
                    else
                        printf("Arquivos Gerados com Sucesso!\n");
                }
                else
                    continue;
                break;

            case 'C':
                
                for(int index = 0; index < 3; index++){
                    pFileName = OpenFileRead(file_names[index].word);    
                    recebe[index] = GenVector(recebe[index], pFileName, &MAX_LEN_VET[index] , &LEN_WORD_TEXT[index]);
                    fclose(pFileName);
                }
                break;

            case 'M':

                printf("\n\n");
                if(MAX_LEN_VET[1]  == 0){
                    printf("Gere os vetores primeiro!!\n");
                    break;
                }
                else
                    for(int index = 0; index < 3; index++)
                        printf("%s => Palavras diferentes: %i\n",file_names[index].word, MAX_LEN_VET[index]);
                break;

            case 'S':
                break;
                
        }
    }

    for(int index = 0; index < 3; index++){
        FreeVector(recebe[index],MAX_LEN_VET[index]);
        free(vector_string[index].word);
    }
    
    free(vector_string);
    return 0;
}
