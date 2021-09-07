#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H


struct manipuleted_string{
    char* word;
};
typedef struct manipuleted_string MAN_String;

int EndOfWord(char chr);
char* ToLowerString(char* ptr_string);
MAN_String* SplitWords(MAN_String* string_vector, char* word, int* len_MAN_String);
#endif
