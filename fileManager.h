//
// Created by andre on 24/08/2021.
//

#ifndef EDA_TP1_FILEMANAGER_H
#define EDA_TP1_FILEMANAGER_H

FILE *openFile(char *filename);

FILE *writeFile(char *filename);

int isNumber(char c);

int isEndWord(char c);

int countCharsInFile(FILE *fileName);

int wordCountInFile(char *word, FILE *fp);

int numberOfWordsInFile(FILE *fp);

int checkForRepeatedWords2(char *word, FILE *fp);

int sortByRating(FILE *Reviews, FILE *Nota1, FILE *Nota2, FILE *Nota3, FILE *Nota4, FILE *Nota5);

#endif //EDA_TP1_FILEMANAGER_H
