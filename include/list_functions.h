#include <stdio.h>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include <assert.h>
#include <cstdarg>

#ifndef TYPES
#include "types.h"
#endif

#ifndef OUTPUT
#include "output.h"
#endif

extern "C" int MyOwnStrncmp(char*, char*);

// int FindIndexOfFirstElemWithThisHashNum(list_t* list, int hashnum, more_list_el_t* arr_of_first_hashnum_with_size);
// int FindTheSameWord(list_t* list, hashtable_type* first_elem_with_this_hashnum, char* word);
// int FindIndexOfLastElemWithThisHashNum(list_t* list, int hashnum);
void FillHashTable(hashtable_type* hashtable, char* word, unsigned int hashnum);
int FindSomeElementsInTable(hashtable_type* hashtable, char** arr_of_words);
int MyStrcmp(char* word1, char* word2);
char** MakeArrOfWordsFromOneBuf(char* buf, int bufsize);
hashtable_el_type* FindOneElInTable(hashtable_type* hashtable, char* word);
