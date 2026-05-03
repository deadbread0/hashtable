#include <stdio.h>
#include "types.h"
#include "init.h"
#include "input.h"
#ifndef OUTPUT
#include "output.h"
#endif
#include "time.h"
// gcc -no-pie stdprintf.c myprintf.o -o new

int main()
{
    FILE* output_file = fopen(NAME_OF_OUTPUT_FILE, "w");
    FILE* input_file = fopen(NAME_OF_BIG_INPUT_FILE, "r");

    int input_file_size = GetSizeOfInputFile(NAME_OF_BIG_INPUT_FILE);
    
    char* buf = InitBuf(input_file_size);

    ReadText(input_file, buf, input_file_size);

    FillFileWithWords(output_file, buf, input_file_size); 

    fclose(output_file);
    fclose(input_file);

    hashtable_type hashtable[INITIAL_SIZE] = {};
    InitList(hashtable);

    InputFromFile(NAME_OF_OUTPUT_FILE, hashtable); //тут же и заполняется хт
    char** arr_of_words = MakeArrOfWordsFromOneBuf(buf, hashtable->num_of_words);

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (volatile int i = 0; i < 1000; i++)
        int amount_of_found_words = FindSomeElementsInTable(hashtable, arr_of_words);

    struct timespec finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    DumpHT(hashtable);

    fprintf(stderr, "%ld msec\n", finish.tv_sec * 1000 + finish.tv_nsec / 1000000 - start.tv_sec * 1000 + start.tv_nsec / 1000000);
    CSVoutput(hashtable);
    DestroyTable(hashtable);

    for (int i = 0; i < hashtable->num_of_words; i++)
        free(arr_of_words[i]);
        
    free(arr_of_words);
    free(buf);
}