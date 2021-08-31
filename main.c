#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fileManager.h"

void menu() {
    printf("\n|~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~|\n");
    printf("| 1 - Ler o dataset do Trip Advisor  |\n");
    printf("| 2 - Gerar vocabulario              |\n");
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
                int i, numberOfWords, j = 0, t, nWords = 0;
                char word[40];
                char *allWords;

                Nota1 = fopen("./files/Nota1.txt", "r");
                
                numberOfWords = countWordCharInFile(Nota1);
                printf("%d\n", numberOfWords);
                allWords = (char *)malloc(numberOfWords);
                allWords[0] = 0;

                fclose(Nota1);

                Nota1 = fopen("./files/Nota1.txt", "r");

                while((c = fgetc(Nota1)) != EOF){

                    if(!isEndWord(c)) {
                        i = 0;
                        while(!isEndWord(c)) {
                            word[i] = c;
                            c =fgetc(Nota1);
                            i++;
                        }
                        word[i] = ' ';

                        if(i > 3) {
                            printf("%d", checkForRepeatedWords(word, allWords));
                            //if(!checkForRepeatedWords(word, allWords)) {
                                i = 0;
                               // printf("%s", word);
                                while(word[i] != '\0') {
                                    allWords[j] = word[i];
                                    i++;
                                    j++;
                                }
                                nWords ++;
                            //}

                        }

                        memset(word, 0, 40);

                    } 

                }
                  
                printf("printing words...");
                //printf("%s", allWords);
                printf("Numero de palavras: %d\n", nWords);

                free(allWords);

                //Gerar vocabulario
                break;
            case 3:
                //Exibir TF-IDFs. Vide formato na Tabela 1.
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
    return 0;
}
