#include <stdio.h>
#include <stdlib.h>
#ifndef TYPES
#include "types.h"
#endif

void DestroyTable(hashtable_type* hashtable);
void DestroyBuf(char* buf);
void CleanMemory(char** arr_of_words, hashtable_type* hashtable);