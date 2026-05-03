#include "stdio.h"

#ifndef TYPES
#include "types.h"
#endif

#include <stdlib.h>
#include <assert.h>
#include "verification.h"
#include "hash_functions.h"

const int INITIAL_SIZE = 4421; //дада тот самый amount of backets

// hashtable_type* InitHashTable();
char* InitBuf(int size);
// void InitList(list_t* list);
void InitList(hashtable_type* hashtable);
