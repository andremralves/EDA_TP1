    //
    // Created by andre on 24/08/2021.
    //
#include <stdio.h>
#include <string.h>
#include "fileManager.h"

FILE *openFile(char *filename) {
    return fopen(filename, "r");
}

FILE *writeFile(char *filename) {
    return fopen(filename, "w");
}

int isNumber(char c) {
    if(c >= 48 && c <= 57) {
        return 1;
    }
    return 0;
}

int isEndWord(char c){
    int isEnd = 0, i;
    char ends[8] = {' ', ',', ';', '\n', '.', ':', '\\', '/'};
    for(i = 0; i<8; i++){
        if(c == ends[i]){
            isEnd = 1;
            break;
        }
    }
    return isEnd;
}

int countCharsInFile(FILE *fileName) {
    int count = 0, i;
    char word[30], c;

    while((c = fgetc(fileName)) != EOF){

        if(!isEndWord(c)) {
            i = 0;

            while(!isEndWord(c)) {
                word[i] = c;
                c = fgetc(fileName);
                i++;
            }

            if(i > 3) {
                i ++;
                count = count + i;
            }
        } 
    }
    return count;
}

int wordCountInFile(char *word, FILE *fp) {
    int count = 0, i;
    char wordInFile[100], c;
    
    fseek(fp, 0, SEEK_SET);
    while((c = fgetc(fp)) != EOF) {
        i = 0;
        
        while(!isEndWord(c)) {
            wordInFile[i] = c;
            c = fgetc(fp);
            i++;
        }

        if(strcmp(word, wordInFile) == 0)
            count++;

        memset(wordInFile, 0, 100);
    }
    //if(count > 0)
    //    printf("%d ", count); 
    return count;
}

int numberOfWordsInFile(FILE *fp) {
    int count = 1;
    char c;

    fseek(fp, 0, SEEK_SET);
    while((c = fgetc(fp)) != EOF) {
        if(isEndWord(c))
            count++;
    }
    return count;
}

int checkForRepeatedWords(char *word, FILE *fp, long int wordPosition){
    char c, word2[50];
    int i;
   
    //printf("%s\n", word); 
    fseek(fp, 0, SEEK_SET); 
    //printf("%ld\n", ftell(fp));
    //printf("%ld\n", wordPosition);
    c = fgetc(fp);
    //printf("%c\n", c);
    while(ftell(fp) <  wordPosition) {
        //printf("%c", c);
        //printf("%ld ", ftell(fp));
        if(c == '"') {
            while((c = fgetc(fp)) != '"') {
                i = 0;
                while(!isEndWord(c)) {
                    word2[i] = c;
                    c = fgetc(fp);
                    i++;
                }
                word2[i] = ' ';
                //printf("%s", word2);
                if(strcmp(word,word2) == 0)
                     return 1;

                memset(word2, 0, 50);
           }
        }

        c = fgetc(fp);
    }
    //printf("%ld ", ftell(fp));
    return 0;
}

int checkForRepeatedWords2(char *word, FILE *fp){
    char c, word2[100];
    int i;

    fseek(fp, 0, SEEK_SET);
    //printf("%ld", ftell(fp)); 
    //printf("%s", word);
    while((c = fgetc(fp)) != EOF) {
        i = 0;
        //printf("%c", c);
        while(c != '\n') {
            //printf("%c", c);
            word2[i] = c;
            c = fgetc(fp);
            i++;
        } 
        word2[i] = '\n';
        //printf("\n"); 
        //printf("%s ", word2);
        if(strcmp(word, word2) == 0)
            return 1;

        memset(word2, 0, 100);
    }
        //printf("%ld", ftell(fp)); 
    return 0;
}

int sortByRating(FILE *Reviews, FILE *Nota1, FILE *Nota2, FILE *Nota3, FILE *Nota4, FILE *Nota5) {
    char buff[20000], c;
    int i;

    c = fgetc(Reviews);
    while (c != EOF) {
        if(c == '"') {
            memset(buff, 0, 20000);
            c = fgetc(Reviews);
            i = 0;
            while (c != '"') { //le todos os caracteres entre aspas
                buff[i] = c;   // adiciona o caracter do arquivo a um vetor
                c = fgetc(Reviews); // passa para o proximo caracter
                i++;
            }
            buff[i] = '\n';
        }

        switch (c) {
            case '1':
                fputs(buff, Nota1);
                break;
            case '2':
                fputs(buff, Nota2);
                break;
            case '3':
                fputs(buff, Nota3);
                break;
            case '4':
                fputs(buff, Nota4);
                break;
            case '5':
                fputs(buff, Nota5);
                break;
            default:
                break;
        }

        c = fgetc(Reviews); //anda para o proximo caractere
    }
    memset(buff, 0, 20000);
    return 0;
}
