#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "read_csv.h"
#define LEN_STR_FILE 40


int main() {
    char nomearquivo[LEN_STR_FILE];
    scanf("%s",nomearquivo);
    FILE* pFileName = Open_file_read(nomearquivo);
    bool flag = Separa_por_nota(pFileName);
    return 0;
}
