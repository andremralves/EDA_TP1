#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fileManager.h"
#include <math.h>

void menu() {
    printf("\n|~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~|\n");
    printf("| 1 - Ler o dataset do Trip Advisor  |\n");
    printf("| 2 - Gerar vocabulario              |\n");
    printf("| 3 - Gerar todos os TF-IDFs         |\n");
    printf("| 0 - Sair                           |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n");
    printf("Escolha uma opcao do menu: ");
}

int main() {
    int menuNum;
    char fileName[30];

    FILE *Reviews = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    FILE *vocabulary = NULL;
    FILE *allTFIDF = NULL;

    //case2
    
    char c;
    char word[100];
    int i, count = 0;
    long int filePos;

    do {
        menu();
        scanf("%d", &menuNum);
        switch (menuNum) {
            case 1:
                printf("Digite o nome do arquivo: ");
                scanf("%s", fileName); //../files/reviews.csv

                Reviews = openFile(fileName);

                if(Reviews == NULL) {
                    printf("Arquivo nao foi lido!\n");
                    break;
                }
               
                Nota1 = fopen("./files/Nota1.txt", "w");
                Nota2 = fopen("./files/Nota2.txt", "w");
                Nota3 = fopen("./files/Nota3.txt", "w");
                Nota4 = fopen("./files/Nota4.txt", "w");
                Nota5 = fopen("./files/Nota5.txt", "w");

                sortByRating(Reviews, Nota1, Nota2, Nota3, Nota4, Nota5);
                break;
            case 2:
                char c;
                char word[100];
                int i, count = 0;
                long int filePos;

                if(Reviews != NULL) 
                    fclose(Reviews);

                Reviews = fopen("./files/reviews.csv", "r");
                vocabulary = fopen("./files/vocabulary.txt", "w+");

                printf("Adicionando o vocabulario no arquivo vocabulary.txt");
                while((c = fgetc(Reviews)) != EOF) {
                    if(c == '"') {
                        while((c = fgetc(Reviews)) != '"') {
                            i = 0;
                            filePos = ftell(vocabulary);
                            //printf("%ld", filePos);
                            while(!isEndWord(c)) {
                                //fputc(c, vocabulary);
                                word[i] = c;
                                c = fgetc(Reviews); 
                                i++;
                            }
                            //fputc(c, vocabulary);
                            word[i] = '\n';
                            //printf("%s", word);
                            if(i > 3) {
                                //printf("%d ", checkForRepeatedWords2(word, vocabulary));
                                if(!checkForRepeatedWords2(word, vocabulary)){
                                    //fseek(vocabulary, filePos, SEEK_SET);
                                    fputs(word, vocabulary);
                                    //fputc('\n', vocabulary);
                                    count ++;
                                    //printf("adding %s", word);
                                }
                            }

                            memset(word, 0, 100); 
                        }
                        //fputc('\n', vocabulary);
                    }
                } 
                //Gerar vocabulario
                break;
            case 3:
                char str[200];
                int wordCountN1, wordCountN2, wordCountN3, wordCountN4, wordCountN5, nWordsN1, nWordsN2, nWordsN3, nWordsN4, nWordsN5;
                double nDocWithWord;
                double TF_IDF1, TF_IDF2, TF_IDF3, TF_IDF4, TF_IDF5, IDF, TF1, TF2, TF3, TF4, TF5, x; 
                if(vocabulary != NULL)
                    fclose(vocabulary);

                if(Nota1 != NULL) {
                    fclose(Nota1);
                    fclose(Nota2);
                    fclose(Nota3);
                    fclose(Nota4);
                    fclose(Nota5);
                }
                
                vocabulary = fopen("files/vocabulary.txt", "r");
                Nota1 = fopen("files/Nota1.txt", "r");
                Nota2 = fopen("files/Nota2.txt", "r");
                Nota3 = fopen("files/Nota3.txt", "r");
                Nota4 = fopen("files/Nota4.txt", "r");
                Nota5 = fopen("files/Nota5.txt", "r");
                allTFIDF = fopen("files/allTFIDF.csv", "w");

                nWordsN1 = numberOfWordsInFile(Nota1);
                nWordsN2 = numberOfWordsInFile(Nota2);
                nWordsN3 = numberOfWordsInFile(Nota3);
                nWordsN4 = numberOfWordsInFile(Nota4);
                nWordsN5 = numberOfWordsInFile(Nota5);

                printf("Vocabulario    Nota1    Nota2    Nota3    Nota4    Nota5\n"); 
                fputs("Vocabulario,Nota1,Nota2,Nota3,Nota4,Nota5\n", allTFIDF);
                while((c = fgetc(vocabulary)) != EOF) {
                    i = 0;
                    nDocWithWord = 0;

                    //ler cada palavra do arquivo
                    while(!isEndWord(c)) {
                        word[i] = c;
                        c = fgetc(vocabulary);
                        i++;
                    }
                   
                    wordCountN1 = wordCountInFile(word, Nota1);  
                    wordCountN2 = wordCountInFile(word, Nota2);  
                    wordCountN3 = wordCountInFile(word, Nota3);  
                    wordCountN4 = wordCountInFile(word, Nota4);  
                    wordCountN5 = wordCountInFile(word, Nota5);

                    if(wordCountN1)
                        nDocWithWord++;
                    if(wordCountN2)
                        nDocWithWord++;
                    if(wordCountN3)
                        nDocWithWord++;
                    if(wordCountN4)
                        nDocWithWord++;
                    if(wordCountN5)
                        nDocWithWord++;
                    
                    if(nDocWithWord == 0)
                        nDocWithWord = 1;

                    x = 5.0/nDocWithWord; 
                    IDF = log10(x); 
                    TF1 = wordCountN1/nWordsN1;
                    TF2 = wordCountN2/nWordsN2;
                    TF3 = wordCountN3/nWordsN3;
                    TF4 = wordCountN4/nWordsN4;
                    TF5 = wordCountN5/nWordsN5;

                    TF_IDF1 = TF1 * IDF; 
                    TF_IDF2 = TF2 * IDF;
                    TF_IDF3 = TF3 * IDF;
                    TF_IDF4 = TF4 * IDF;
                    TF_IDF5 = TF5 * IDF;

                    printf("%lf | %d | %d | %.10lf | %.10lf | %.10lf\n",nDocWithWord, wordCountN1, nWordsN1, TF1, IDF, TF_IDF1);
                     
                    sprintf(str, "\"%s\",%.15lf,%.15lf,%.15lf,%.15lf,%.15lf\n", word, TF_IDF1, TF_IDF2, TF_IDF3, TF_IDF4, TF_IDF5);

                    fputs(str, allTFIDF);
                    //printf("%s  |  %d\n", word, wordCountN1);

                    memset(word, 0, 100);
                }

                break;
            case 4:
                //Exibir TF-IDF de uma Nota. Em ordem decrescente de valor de TF-IDF
                //Usuário deve informar qual TF-IDF a ser visualizado (da nota 1,2,3,4 ou 5).
                // Vide formato na Tabela 2.
                break;
            case 5:
                //Exibir TF-IDFs. Vide formato na Tabela 1.
                break;
            case 0:
                break;
            default:
                printf("Digite um numero valido!\n");
                break;
        }
    } while (menuNum != 0);

    fclose(Reviews);
    fclose(Nota1);
    fclose(Nota2);
    fclose(Nota3);
    fclose(Nota4);
    fclose(Nota5);
    fclose(vocabulary);
    fclose(allTFIDF);
    return 0;
}
