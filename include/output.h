#define OUTPUT
#include <stdio.h>
#include <cstdlib>
#include <ctype.h>
#include <assert.h>

#ifndef TYPES
#include "types.h"
#endif

static const char* NAME_OF_OUTPUT_FILE = "files/words.txt";
static const char* NAME_OF_DUMP_FILE = "files/hashtable_info.txt";
static const char* NAME_OF_INFO_FILE = "files/hashtable_info.txt";

bool FillFileWithWords(FILE* output_file, char* buf, int bufsize);
void SkipNotLeller(char* buf, int *i); 
void CSVoutput(hashtable_type* hashtable);
void DumpHT(hashtable_type* hashtable, long long int time);
float CountVariance(hashtable_type* hashtable);
float CountLoadFactor(hashtable_type* hashtable);