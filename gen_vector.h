#ifndef GEN_VECTOR_H
#define GEN_VECTOR_H
#include <stdio.h>

struct word{
  char* word;
  int num;
};
typedef struct word Word;

void VerifyAllocation(void* pointer);
void FreeVector(Word* vector, int len_vector);
Word* AllocSpace(Word* source,int max_len_vetor, int insert_pos);
Word* CopyData(Word* source, Word* dest, int len_source, int insert_pos);
Word* InsertSort(Word* source,int* max_len_vetor, char* element);
Word* GenVector(Word* source, FILE* pFileName,int* len_source, int* LEN_WORD_TEXT);
int FinPos(Word* source,int* max_len_vetor,char* element);
#endif

