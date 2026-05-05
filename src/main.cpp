#include <stdio.h>
#include <x86intrin.h>
#include "types.h"
#include "init.h"
#include "input.h"
#ifndef OUTPUT
#include "output.h"
#endif
#include "free_memory.h"

int main()
{
    int input_file_size = GetSizeOfInputFile(NAME_OF_BIG_INPUT_FILE);
    char* buf = InitBuf(input_file_size);

    GetWordsFromFile(input_file_size, buf);
    
    hashtable_type hashtable[INITIAL_SIZE] = {};
    InitList(hashtable);

    InputFromFile(NAME_OF_OUTPUT_FILE, hashtable); //тут же и заполняется хт
    char** arr_of_words = MakeArrOfWordsFromOneBuf(buf, hashtable->num_of_words);

    unsigned long long int start, end = 0;
    start = __rdtsc();

    for (volatile int i = 0; i < 1000; i++)
        int amount_of_found_words = FindSomeElementsInTable(hashtable, arr_of_words);

    end = __rdtsc();

    DumpHT(hashtable, end - start);
    CSVoutput(hashtable);

    DestroyTable(hashtable);
    CleanMemory(arr_of_words, hashtable);
    DestroyBuf(buf);
}