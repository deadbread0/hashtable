#include "init.h"

char* InitBuf(int size)
{
    char* buf = (char*)calloc(size, sizeof(char));
    if (buf == nullptr)
        printf("memory allocation memory\n");

    return buf;
}

void InitList(hashtable_type* hashtable)
{
    assert(hashtable != nullptr);

    hashtable_el_type* data = (hashtable_el_type*)calloc(INITIAL_SIZE, sizeof(hashtable_el_type));//
    hashtable->hash_table = data;
    hashtable->num_of_words = 0;
    hashtable->size = INITIAL_SIZE;
    hashtable->func = CRC32ASM;

}