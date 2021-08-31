#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct palavra{
    char* string;
    int num_vezes;
};
typedef struct palavra Palavra; 

Palavra* CopiaDados(Palavra* origem, Palavra* destino, int PosicaoLivre, int LenOrigem){
    int IndexOrig = 0;
    for(int i = IndexOrig; i < LenOrigem + 1; i++){
        if(i == PosicaoLivre)
            continue;
        else{
            destino[i].string = (char*)calloc(strlen(origem[IndexOrig].string),sizeof(char));
            strcpy(destino[i].string,origem[IndexOrig].string);
            IndexOrig++;
        }
    }
    return  destino;
}

Palavra* AlocaEspaco(Palavra* origem,int MaxLenVetor, int PosicaoLivre){
    Palavra* vet_retorno = (Palavra*)calloc(MaxLenVetor + 1,sizeof(Palavra));
    vet_retorno = CopiaDados(origem,vet_retorno,PosicaoLivre,MaxLenVetor);
    free(origem);
    return vet_retorno; 
}


int findPos(Palavra* palavras,int NumElementos, char* elemento){
    int i, inicio, meio, final;
    inicio = 0;
    final = NumElementos - 1;
    if(strcmp(elemento,palavras[0].string) < 0){
        return 0;
    }
    while(inicio <= final){
        meio = (inicio + final)/2;
        if(strcmp(elemento,palavras[meio].string) < 0){
            final = meio - 1;
        }
        else{
            if(strcmp(elemento,palavras[meio].string) > 0){
                inicio = meio + 1;
            }
            else{
                palavras[meio].num_vezes++;
                return -1;
            
            }
        }
    }
    
    if(strcmp(elemento,palavras[meio].string) < 0)
        return meio;
    else
        return meio +1;
}

Palavra* InsereOrdenado(Palavra* vetor, char* palavra_procurada, int* MaxLenVetor){
    int posicao_insercao;
    if(*MaxLenVetor == 0){
        vetor = (Palavra*)malloc(sizeof(Palavra)*1);
        vetor[0].string = (char*)calloc(strlen(palavra_procurada),sizeof(char));
        strcpy(vetor[0].string,palavra_procurada);
        (*MaxLenVetor)++;
        return  vetor;
    }
    else{
        posicao_insercao = findPos(vetor,*MaxLenVetor,palavra_procurada);
        if(posicao_insercao >= 0){
            vetor = AlocaEspaco(vetor,*MaxLenVetor, posicao_insercao);
            vetor[posicao_insercao].string = (char*)calloc(strlen(palavra_procurada),sizeof(char));
            strcpy(vetor[posicao_insercao].string,palavra_procurada);
            (*MaxLenVetor)++;
        }
    }
    return vetor;
}
int main(){    
    Palavra *palavras, *novo_vetor;
    char* palavra_insere1 = "abacaxi";
    char* palavra_insere2 = "abacate";
    char* palavra_insere3 = "cachorro";
    char* palavra_insere4 = "zzz";
    int MaxLenVetor = 0;
    
    palavras = NULL;

    palavras = InsereOrdenado(palavras,palavra_insere1,&MaxLenVetor); 
    palavras = InsereOrdenado(palavras,palavra_insere3,&MaxLenVetor); 
    palavras = InsereOrdenado(palavras,palavra_insere2,&MaxLenVetor);
    //palavras = InsereOrdenado(palavras,palavra_insere2,&MaxLenVetor);
    //for(int i = 0; i < 3; i++){
    //    printf("%s\n",palavras[i].string);
    //}
    return 0;
}
