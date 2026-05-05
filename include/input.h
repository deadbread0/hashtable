#include "stdio.h"

#ifndef TYPES
#include "types.h"
#endif

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include "list_functions.h"

static const char* NAME_OF_INPUT_FILE1 = "files/tolstoy.txt";
static const char* NAME_OF_INPUT_FILE2 = "files/hallaron.txt";
static const char* NAME_OF_INPUT_FILE3 = "files/harrypotter.txt";
static const char* NAME_OF_BIG_INPUT_FILE = "files/3in1.txt";

int GetSizeOfInputFile(const char* filee_name);
int ReadText(FILE* filee, char* buf, int size);
void InputFromFile(const char* filee_name, hashtable_type* hashtable);
void GetWordsFromFile(int input_file_size, char* buf);
