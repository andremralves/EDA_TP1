#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(){
    int MenuOption;

    printf("\n==================== M E N U ====================\n\n"
           "                   Selecione...                    \n\n"
           "1 - Para ler um database do Trip Advisor             \n"
           "2 - Exibir TF-IDF de uma nota                        \n"
           "3 -                                                  \n"
           "4 - Para sair...                                     \n"
           "\n=================================================\n\n");

    scanf("%d", &MenuOption);
    printf("\n");
    return MenuOption;
}
int OrganizeDB(){
    FILE *Input = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    
    char File[30];
    printf("\nInsira o nome do arquivo desejado: ");
    scanf("%s", File);
    Input = fopen(File, "r");
    
    if(Input == NULL){
        printf("Arquivo %s invalido!\nTente novamente!\n", File);
        return 0;
    }else{
        printf("\nArquivo %s validado com sucesso!\n\n", File);
        printf("Analisando arquivo...\n");
    }
    char reader, Comment[20000];
    int i;
    reader = fgetc(Input + '\n');
    Nota1 = fopen("Nota1.txt", "w");
    Nota2 = fopen("Nota2.txt", "w");
    Nota3 = fopen("Nota3.txt", "w");
    Nota4 = fopen("Nota4.txt", "w");
    Nota5 = fopen("Nota5.txt", "w");
    
    while(!feof(Input)){
        if(reader == '"'){
            memset(Comment, 0, 20000);
            reader = fgetc(Input);
            i = 0;
            while(reader != '"'){
                Comment[i] = reader;
                reader = fgetc(Input);
                i++;
            }
            Comment[i] = '\n';
        }
        switch (reader){
            case '1':
                fputs(Comment, Nota1);
                printf("Nota 1...\n");
                break;
            case '2':
                fputs(Comment, Nota2);
                printf("Nota 2...\n");
                break;
            case '3':
                fputs(Comment, Nota3);
                printf("Nota 3...\n");
                break;
            case '4':
                fputs(Comment, Nota4);
                printf("Nota 4...\n");
                break;
            case '5':
                fputs(Comment, Nota5);
                printf("Nota 5...\n");
                break;
            default:
                break;
        }
        reader = fgetc(Input);
    }   
    memset(Comment, 0, 20000);
    printf("\nProcessamento finalizado!\n");

    if(Nota1 != NULL || Nota2 != NULL || Nota3 != NULL || Nota4 != NULL || Nota5 != NULL){
        printf("Arquivos organizados com sucesso!\n");}
    else{
        printf("Erro!\nArquivos nao foram organizados!\n");}
    
    fclose(Input);
    fclose(Nota1);
    fclose(Nota2);
    fclose(Nota3);
    fclose(Nota4);
    fclose(Nota5);
    reader = NULL;
    return 0;
}
int Vocabulary(){
    int txtOption;
    FILE *Nota = NULL;
    printf("                                                \n"
           "Selecione o arquivo que gostaria de analisar: \n\n"
           "1 - Nota 1                                      \n"
           "2 - Nota 2                                      \n"
           "3 - Nota 3                                      \n"
           "4 - Nota 4                                      \n"
           "5 - Nota 5                                      \n"
           "                                                \n");
    scanf("%d", &txtOption);

    switch (txtOption){
        case 1:
            Nota = fopen("Nota1.txt", "r");
            break;
        case 2:
            Nota = fopen("Nota2.txt", "r");
            break;
        case 3:
            Nota = fopen("Nota3.txt", "r");
            break;
        case 4:
            Nota = fopen("Nota4.txt", "r");
            break;
        case 5:
            Nota = fopen("Nota5.txt", "r");
            break;
        default:
            printf("Valor invalido!\nTente novamente!\n");
            break;
    }
    if(Nota == NULL){
        printf("\nArquivo txt não encontrado!\nVerifique se o arquivo esta disponivel\n");
    }
    else{
        printf("\nPreparando arquivo Nota%d.txt para analise...\n", txtOption);
        printf("Gerando vocabulario...\n\n");
    }
    char reader, MainWord[50];
    int c, words = 0;
    FILE *CV = NULL;
    CV = fopen("CompareVocabulary.txt", "w");
    reader = fgetc(Nota);
    while(!feof(Nota)){
        memset(MainWord, 0, 50);
        if(reader == 'A' || reader == 'B' || reader == 'C' || reader == 'D' || reader == 'E' || reader == 'F' || reader == 'G' || reader == 'H' || reader == 'I' || reader == 'J' || reader == 'K' || reader == 'L' || reader == 'M' || reader == 'N' || reader == 'O' || reader == 'P' || reader == 'Q' || reader == 'R' || reader == 'S' || reader == 'T' || reader == 'U' || reader == 'V' || reader == 'W' ||reader == 'X' || reader == 'Y' || reader == 'Z' || reader == 'a' || reader == 'b' || reader == 'c' || reader == 'd' || reader == 'e' || reader == 'f' || reader == 'g' || reader == 'h' || reader == 'i' || reader == 'j' || reader == 'k' || reader == 'l' || reader == 'm' || reader == 'n' || reader == 'o' || reader == 'p' || reader == 'q' || reader == 'r' || reader == 's' || reader == 't' || reader == 'u' || reader == 'v' || reader == 'w' || reader == 'x' || reader == 'y' || reader == 'z'){     
            c = 0;
            while(reader == 'A' || reader == 'B' || reader == 'C' || reader == 'D' || reader == 'E' || reader == 'F' || reader == 'G' || reader == 'H' || reader == 'I' || reader == 'J' || reader == 'K' || reader == 'L' || reader == 'M' || reader == 'N' || reader == 'O' || reader == 'P' || reader == 'Q' || reader == 'R' || reader == 'S' || reader == 'T' || reader == 'U' || reader == 'V' || reader == 'W' ||reader == 'X' || reader == 'Y' || reader == 'Z' || reader == 'a' || reader == 'b' || reader == 'c' || reader == 'd' || reader == 'e' || reader == 'f' || reader == 'g' || reader == 'h' || reader == 'i' || reader == 'j' || reader == 'k' || reader == 'l' || reader == 'm' || reader == 'n' || reader == 'o' || reader == 'p' || reader == 'q' || reader == 'r' || reader == 's' || reader == 't' || reader == 'u' || reader == 'v' || reader == 'w' || reader == 'x' || reader == 'y' || reader == 'z'){
                MainWord[c] = reader;
                reader = fgetc(Nota);
                c++;
            }
            if(c < 3){
                memset(MainWord, 0, 50);
                c = 0;
            }
            else{
                MainWord[c] = '\n';
                printf("%s", MainWord);
                fputs(MainWord, CV);
                words++;
            }
        }
        reader = fgetc(Nota);
    }
    printf("\n%d palavras\n\n", words);
    printf("Arquivo 'CompareVocabulary.txt' criado!\n\n"); 

    fclose(Nota);
    return 0;
}

int main(){
    int MenuOption;
    do{
        MenuOption = menu();
        switch(MenuOption)
        {
        case 1:
            printf("Ler Database...\n");
            OrganizeDB(); 
            break;
        case 2:
            printf("Gerando TF-IDF...\n");
            Vocabulary();
            break;
        case 3:
            break;
        case 4:
            printf("Saindo...\n\n");
            exit(EXIT_SUCCESS);
        default:
            printf("Opcao invalida! Tente novamente...\n");
            break;
        }
    } while (MenuOption != 2);
    return 0;
}
