#include <stdio.h>
#include <string.h>
#include "fileManager.h"

void menu() {
    printf("\n|~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~|\n");
    printf("| 1 - Ler o dataset do Trip Advisor  |\n");
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

                Nota1 = writeFile("../files/Nota1.txt");
                Nota2 = writeFile("../files/Nota2.txt");
                Nota3 = writeFile("../files/Nota3.txt");
                Nota4 = writeFile("../files/Nota4.txt");
                Nota5 = writeFile("../files/Nota5.txt");

                sortByRating(Reviews, Nota1, Nota2, Nota3, Nota4, Nota5);
                break;
            case 2:
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
