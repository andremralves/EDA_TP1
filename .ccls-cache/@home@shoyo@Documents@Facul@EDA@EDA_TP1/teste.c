#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct palavra{
    char* string;
    int num_vezes;
};
typedef struct palavra Palavra; 

Palavra* CopiaDados(Palavra* origem, Palavra* destino, int PosicaoLivre, int LenOrigem){
    int valor = LenOrigem + 1;
    for(int i = 0; i < valor; i++){
        if(i == PosicaoLivre)
            i++;
        else{
            destino[i].string = (char*)malloc(sizeof(char)*strlen(origem[i].string));
            strcpy(destino[i].string,origem[i].string);
            //printf("%s\n",destino[i].string);
        }
    }
    return  destino;
}

Palavra* AlocaEspaco(Palavra* origem,int MaxLenVetor, int PosicaoLivre){
    Palavra* vet_retorno = (Palavra*)malloc(MaxLenVetor + 1);
    vet_retorno = CopiaDados(origem,vet_retorno,PosicaoLivre,MaxLenVetor);
    //printf("%s",vet_retorno[0].string);
    free(origem);
    return vet_retorno; 
}


int findPos(Palavra* palavras,int NumElementos, char* elemento){
    int i, inicio, meio, final;
    inicio = 0;
    final = NumElementos - 1;
    
    if(strcmp(elemento,palavras[0].string) < 0){
        printf("%s\n",palavras[0].string);
        return 0;
    }
    while(inicio <= final){
        meio = (inicio + final)/2;
        if(strcmp(elemento,palavras[meio].string) < 0){
            //printf("palavra: %s elemento_pos: %s inicio: %i meio: %i final: %i\n",palavras[meio].string,elemento,inicio,meio,final);
            final = meio - 1;
        }
        else{
            if(strcmp(elemento,palavras[meio].string) > 0){
                //printf("palavra: %s elemento_pos: %s inicio: %i meio: %i final: %i\n",palavras[meio].string,elemento,inicio,meio,final);
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
        vetor[0].string = (char*)malloc(sizeof(char)*strlen(palavra_procurada));
        strcpy(vetor[0].string,palavra_procurada);
        (*MaxLenVetor)++;
        //printf("%s\n",vetor[0].string);
        return  vetor;
    }
    else{
        posicao_insercao = findPos(vetor,*MaxLenVetor,palavra_procurada);
        if(posicao_insercao >= 0){
            vetor = AlocaEspaco(vetor,*MaxLenVetor, posicao_insercao);
            vetor[posicao_insercao].string = (char*)malloc(sizeof(char)*strlen(palavra_procurada));
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
    int teste;
    int MaxLenVetor = 0;
    
    palavras = NULL;

    palavras = InsereOrdenado(palavras,palavra_insere2,&MaxLenVetor); 
    palavras = InsereOrdenado(palavras,palavra_insere3,&MaxLenVetor); 
    //teste = findPos(palavras,MaxLenVetor,palavra_insere4);
    //printf("%i",teste);
    palavras = InsereOrdenado(palavras,palavra_insere4,&MaxLenVetor);
    //palavras = InsereOrdenado(palavras,palavra_insere2,&MaxLenVetor);
    for(int i = 0; i < 3; i++){
        printf("%s\n",palavras[i].string);
    }
    return 0;
}
