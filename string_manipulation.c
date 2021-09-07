#include "string_manipulation.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* ToLowerString(char* ptr_string)
{
    char* lower_string =  (char*)calloc(strlen(ptr_string),sizeof(char));    
    for(int index = 0; index < strlen(ptr_string); index++)
        lower_string[index] = tolower(ptr_string[index]); 
    return lower_string; 
}

int EndOfWord(char chr){ //  função ponta ja utilizada no exercio anterior
    int index, FINAL_FLAG = 0;
    char ENDWRL[6] = {'\n', ' ', '.', ',', ';', ':'};
    int TAMFIMPAL = 6;

    for(index = 0; index < TAMFIMPAL; index++){
        if(chr == ENDWRL[index]){
            FINAL_FLAG = 1;
            break;
        }
    }
    return FINAL_FLAG;
}

MAN_String* SplitWords(MAN_String* string_vector, char* string, int* len_MAN_String)
{
    //MAN_String* string_vector; // vetor de strings tratadas
    char *ptr_start; // ponteiros que vao indicar inicio de uma palavra dentro de uma string não tratado
    //int insert_pos = 0;   
    int pos_ptr_start = 0; // posição atual do ponteiro start dentro da string 
    ptr_start = string; // ponteiro de inicio aponta para o inicio da string
    string_vector = (MAN_String*)calloc(1, sizeof(MAN_String));
    
    string = ToLowerString(string);

    for(int index = 0; index < strlen(string); index++)
    {

        if(EndOfWord(string[index])){
            string_vector[*len_MAN_String].word = calloc(index - pos_ptr_start -1 ,sizeof(char)); // aloca o tamanho entre a posiçao que encontra a fim da palavra e a posição atual do ptr_start
            memcpy(string_vector[*len_MAN_String].word, ptr_start, index); // copia exatamente o numero de bytes dados pelo index ,da palavra que start aponta para dentro da posição atual de inserção do vetor strings
            if(index + 1 < strlen(string)){ // caso exista posições maiores que index + 1, existem outras palavras
                string_vector = realloc(string_vector,*len_MAN_String + 1); // raloca espaço para mais uma posição 
                (*len_MAN_String)++; // espaço ja alocado, insert_pos agora representa a proxima posição disponivel
                ptr_start = &string[index+1]; // ptr_start aponta para a posição de incio de uma possivel palavra
                pos_ptr_start = index + 1; // pos do ptr_start aponta para inicio de uma nova palavra 
            }
            else
                return string_vector; // se não entrar no if, significa que existe apenas 1 palavra seguida por fim de palavra
        }else
            continue;
    }

    string_vector[*len_MAN_String].word = calloc(strlen(ptr_start),sizeof(char)); // insere a ultima palavra com inicio apontada em ptr_start
    memcpy(string_vector[*len_MAN_String].word, ptr_start, strlen(string)- pos_ptr_start); // copia a string para o vetor de strings
    
    return string_vector;
}
