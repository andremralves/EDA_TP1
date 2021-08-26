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

int sortByRating(FILE *Reviews, FILE *Nota1, FILE *Nota2, FILE *Nota3, FILE *Nota4, FILE *Nota5) {
    char buff[20000], c;
    int i;

    c = fgetc(Reviews);
    while (c != EOF) {
        if(c == '"') {
            memset(buff, 0, 20000);
            c = fgetc(Reviews);
            i = 0;
            while (c != '"') {
                buff[i] = c;
                c = fgetc(Reviews);
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

        c = fgetc(Reviews);
    }
    memset(buff, 0, 20000);
    return 0;
}