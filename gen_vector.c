#include "gen_vector.h"
#include "string_manipulation.h"
#include "MAN_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void VerifyAllocation(void* pointer)
{
    if(pointer == NULL) // verifica se foi alocando memoria
    {
        printf("não foi possivel allocar memoria\n");
        exit(1); // fecha o programa
    }
}

void FreeVector(Word* vector, int len_vector)
{
    for(int index = 0; index < len_vector; index++)
        free(vector[index].word); // libera todos os char* do vetor de origem
    free(vector); // libera o vetor de origem
}

Word* AllocSpace(Word* source,int MaxLenVetor, int insert_pos)
{ 
    Word* dest = (Word*)calloc(MaxLenVetor + 1,sizeof(Word)); //cria vetor de destino do tamanho do vetor atual(origem) + 1
    VerifyAllocation(dest); // verifica se foi allocado
    dest = CopyData(source, dest, MaxLenVetor, insert_pos); // copia dados do meu vetor de origem para o meu vetor de destino
    FreeVector(source,MaxLenVetor); // libera o vetor de origem, os dados ja estao copiados
    return dest;
}

Word* CopyData(Word* source, Word* dest, int len_source, int insert_pos)
{
    int index_source = 0; // cria posição para pegar elementos do vetor de origem
    
    for(int index = 0; index < len_source + 1; index++)
    {
        if(index == insert_pos)
            continue; // ignora codigo abaixo caso encontre a posição que se deseja deixar livre, nao alocando espaço            
        else
        {
            dest[index].word = (char*)calloc(strlen(source[index_source].word), sizeof(char)); //aloca espaço para palavra no vetor de destino do mesmo tamanho da palavra do vetor de origem        
            VerifyAllocation(dest[index].word); // verifica se foi alocado 
            strcpy(dest[index].word, source[index_source].word); // copia a palavra na posição do index da origem no vetor de destino
            dest[index].num = source[index_source].num; // atribui o numero de repetições de uma palavra do vetor origem para o vetor destino
            index_source++; // atrasa a posição dos valores do vetor de origem em relaçao aos do destino
        }
    }
    return  dest; // vetor de destino passa a ser o vetor de origem
}

Word* InsertSort(Word* source, int* max_len_vetor, char* element)
{
    int insert_pos; // variavel que recebe a posição de inserção
    if(*max_len_vetor == 0) // se o vetor estiver vazio
    {
        source = (Word*)calloc(1,sizeof(Word)); // aloca 1 possição para o vetor origem
        VerifyAllocation(source); // verifica se o ponteiro foi alocado
        source[0].word = (char*)calloc(strlen(element),sizeof(char)); // aloca o espaço da primeira possição do mesmo tamanho da nova palavra
        VerifyAllocation(source[0].word);
        strcpy(source[0].word, element); // copia a nova palavra para peimeira posição do vetor origem
        source[0].num++; // palavra inserida, portanto o numero que ela aparece incialmente é 1
        (*max_len_vetor)++; //incrementa o numero maximo de elementos para 1
        return source;
    }
    else
    {
        insert_pos = FinPos(source,max_len_vetor,element); // encontra posição de inserção da palavra
        if(insert_pos >= 0)
        {
            source = AllocSpace(source,*max_len_vetor,insert_pos); // aloca 1 nova posição para o vetor origem
            source[insert_pos].word = (char*)calloc(strlen(element),sizeof(char)); //aloca espaço do mesmo tamanho da nova palavra no vetor origem
            VerifyAllocation(source[insert_pos].word);
            strcpy(source[insert_pos].word,element); //copia a nova palavra para o a posição de inserção do vetor origem
            source[insert_pos].num++; // palavra inserida, portanto o numero minimo que ela aparece é 1
            (*max_len_vetor)++; // incrementa o tamanho do vetor origem em 1 após inserir
        }
    }
    return source;
}

int FinPos(Word* source, int* max_len_vetor,char* element)
{
    int start, mid, final;
    start = 0;
    final = (*max_len_vetor) - 1;
    if(strcmp(element, source[0].word) < 0)
        return  0; // caso strcmp retorne 0 a palavra procurada é menor que a primira posição, portanto retorna que deve ser inserido em 0
    while(start <= final)
    {
        mid = (start + final)/2;
        if(strcmp(element,source[mid].word) < 0)
            final = mid - 1;
        
        else
        {
            if(strcmp(element,source[mid].word) > 0)
                start = mid + 1;
            else
            {
                source[mid].num++; // palavra ja existe na busca, incrementa o numero de vezes que ele aparece
                return  -1; // caso retorne uma posição negativa significa q ela ja apareceu
            }
        }
    }
    if(strcmp(element,source[mid].word) < 0)
        return mid; // retorna a posição que deve ser inserida
    else
        return mid + 1; // significa que a palavra é maior que a palavra encontra na ultima iteração portanto deve retornar posição+1
}

Word* GenVector(Word* source, FILE* pFileName, int *len_source, int* LEN_WORD_TEXT)
{
    MAN_String* vector_string;
    int LEN_QUEUE = 0;
    char* pword;
    vector_string = NULL;
    while(1)
    {
        if(!ReadFile(pFileName,pword) || feof(pFileName))
            break;
        else{
            vector_string = SplitWords(vector_string, pword, &LEN_QUEUE);
            LEN_WORD_TEXT++;
            for(int index = 0; index <= LEN_QUEUE; index++){
                if(strlen(vector_string[index].word) > 3)    
                    source = InsertSort(source, len_source, vector_string[index].word);
                else
                    continue;
            }
            LEN_QUEUE = 0;
        }
    }
    return source;
}
