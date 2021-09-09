#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MAN_csv.h"
#define LENBUFF 5000
#define LEN_STR_FILE 40

FILE* OpenFileRead(char* pFileName){
    return fopen(pFileName,"r"); // abre arquivo para leitura
}

FILE* OpenFileWrite(char* pFileName){
    return fopen(pFileName,"a"); // abri arquivo para escrita no final do arquivo
}

int ReadFile(FILE* file_name, char* pword){
    if(fscanf(file_name,"%s",pword) < 1) // pega palavra do arquivo
        return 0;
    return 1;
}

void DelFiles(void){
    char generic_name_file[9] = {"Nota*.txt"};
    char number_txt_files[5] = {'1','2','3','4','5'};
    int FLAG_DELETE_FILE;
    for(int index = 0; index < 5; index++){
        generic_name_file[4] = number_txt_files[index];
        FLAG_DELETE_FILE = remove(generic_name_file);
        if(FLAG_DELETE_FILE)
            printf("%s Deletado com sucesso\n",generic_name_file);
        else
            printf("%s não esta no diretorio ou não encontrado\n",generic_name_file);
    }
}
bool WriteTxtFiles(char* Text, char Num_file){
    char file_txt_name[9] = {"Nota*.txt"}; // estruruta generica do tipo do nome dos arquivos gerados
    FILE *pTxtFiles = NULL;
    file_txt_name[4] = Num_file;             
    pTxtFiles = OpenFileWrite(file_txt_name); // abre arquivo para leitura
    if(pTxtFiles == NULL)
        printf("não foi possivel abrir o arquivo para escrita\n");
    else
        fprintf(pTxtFiles,"%s\n",Text); // escreve o texto no arquivo 
    fclose(pTxtFiles); 
    return true;
}

bool SplitByRate(FILE* File_csv){
        
    if(File_csv == NULL){
        printf("Arquivo não encontrado!\n");
        return false;// retorna false caso o arquivo nao esteja aberto
    }
    
    char buff[LENBUFF] = "";
    char* Text = NULL;     //
    char* auxText = NULL;  // aponta os ponteiros para NULL
    char Rating;           // variavei auxilizar para separar o texto da nota
    
    int col_cont = 0;      // incia o contador de colunas em 0
    bool sep_flag = false; // flag de retorno para saber se os textos poram separados
    
    auxText = (char*)malloc(sizeof(char)*sizeof(buff)); // aloca os ponteiros auxilixares do tamanho do buffer
    Text = (char*)malloc(sizeof(char)*sizeof(buff));    //

    while(fgets(buff,LENBUFF,File_csv)){
        auxText = strtok(buff,"\""); // faz split das strings quando encontrar o caracter " 
        col_cont = 0;                // 
            
        while(auxText){              // 
            if(col_cont == 0)        // avalia se esta na primeira coluna, coluna de texto
                Text = auxText;      // Text recebe o todo os cracteres antes de "

            if(col_cont == 1){       // caso a coluna seja a numeros 
                Rating = auxText[1]; // Rating recebe a nota em formato de caracter
                sep_flag = WriteTxtFiles(Text,Rating); // escreve o arquivo o Text referente a respctiva nota Rating
            }
            
            auxText = strtok(NULL,"\""); // continua a busca
            col_cont++;                  // incrementa a coluna para o numero da coluna referente a notas
        }
    }
    fclose(File_csv);
    free(auxText);    
    return true;
}

int GenFiles(FILE* pFileName) {
    char file_name[LEN_STR_FILE] = "";
    printf("Digite o nome do arquivo CSV: ");
    scanf("%s",file_name);
    setbuf(stdin, NULL); // coloca NULL no buffer do teclado

    pFileName = OpenFileRead(file_name); // abre p arquivo para leitura
    if(pFileName == NULL){
        printf("Não foi possivel abrir o arquivo CSV para leitura\n"); 
        return  1;
    }
    if(!SplitByRate(pFileName)){  // ler e escevre os texto nos respectivos arquivos .txt
        printf("Não foi possivel escrever nos arquivos de texto\n");
        return 1;
    }
    return 0;
}

