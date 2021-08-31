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
    char ends[6] = {' ', ',', ';', '\n', '.', ':'};
    for(i = 0; i<6; i++){
        if(c == ends[i]){
            isEnd = 1;
            break;
        }
    }
    return isEnd;
}

int countWordCharInFile(FILE *fileName) {
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

int checkForRepeatedWords(char *word, char*wordArray ){
    int i = 0, j, wordLen, isEqual = 0; 
        wordLen = strlen(word);
        //printf("%s", wordArray);
        //printf("%s", word);

        while(wordArray[i] != '\0') {
            j = 0;
            do {
                if(wordArray[i] == word[j]) 
                    isEqual++;
                
                if(isEqual == wordLen)
                    return 1;
                j++, i++;
            } while(wordArray[i] != ' '); 
            i++;
        }

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
