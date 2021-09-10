#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fileManager.h"
#include <math.h>

void menu() {
    printf("\n|~~~~~~~~~~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("| 1 - Ler o dataset do Trip Advisor e separar nos      |\n");
    printf("|     arquivos Nota1, Nota2, Nota3, Nota4 e Nota5      |\n");
    printf("| 2 - Gerar vocabulario em vocabulary.txt              |\n");
    printf("| 3 - Gerar todos os TF-IDFs em allTFIDF.csv           |\n");
    printf("| 4 - Printar TF-IDF em ordem decrescente              |\n");
    printf("| 0 - Sair                                             |\n");
    printf("| Obs: os arquivos gerados estão na pasta /files       |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n");
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

    //case3
    
    char str[200];
    double wordCountN1, wordCountN2, wordCountN3, wordCountN4, wordCountN5, nWordsN1, nWordsN2, nWordsN3, nWordsN4, nWordsN5;
    double nDocWithWord;
    double TF_IDF1, TF_IDF2, TF_IDF3, TF_IDF4, TF_IDF5, IDF, TF1, TF2, TF3, TF4, TF5, x;

    do {
        menu();
        scanf("%d", &menuNum);
        switch (menuNum) {
            case 1:
                printf("-> ./files/reviews.csv\n");
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

                printf("Arquivos Nota1.txt, Nota2.txt, Nota3.txt, Nota4.txt e Nota5.txt foram gerados com sucesso!\n");
                break;
            case 2:

                printf("Adicionando o vocabulario no arquivo vocabulary.txt");
                if(Reviews != NULL) 
                    fclose(Reviews);
                
                if(vocabulary != NULL)
                    fclose(vocabulary);

                Reviews = fopen("./files/reviews.csv", "r");
                vocabulary = fopen("./files/vocabulary.txt", "w+");

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

                printf("Gerando o arquivo dos TF-IDFs...\n"); 
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
                    
                    //calcula o TF-IDF
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

                    sprintf(str, "\"%s\",%.10lf,%.10lf,%.10lf,%.10lf,%.10lf\n", word, TF_IDF1, TF_IDF2, TF_IDF3, TF_IDF4, TF_IDF5);

                    fputs(str, allTFIDF);
                    //printf("%s  |  %d\n", word, wordCountN1);

                    memset(word, 0, 100);
                }

                break;
            case 4:

                if(allTFIDF != NULL)
                    fclose(allTFIDF);

                allTFIDF = fopen("./files/allTFIDF.csv", "r");
               
                printf("-> nota1, nota2, nota3, nota4 ou nota5\n");
                printf("Digite o TF-IDF a ser visualizado: ");
                scanf("%s", fileName);
                if(strcmp(fileName, "nota1") == 0) { 
                    sortTFIDF(allTFIDF, 1);
                    break;
                } else if(strcmp(fileName, "nota2") == 0) {
                    sortTFIDF(allTFIDF, 2);
                    break;
                } else if(strcmp(fileName, "nota3") == 0) {
                    sortTFIDF(allTFIDF, 3);
                    break;
                } else if(strcmp(fileName, "nota4") == 0) {
                    sortTFIDF(allTFIDF, 4);
                    break;
                } else if(strcmp(fileName, "nota5") == 0) {
                    sortTFIDF(allTFIDF, 5);
                    break;
                } else
                    printf("Entrada inválida\n"); 

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
