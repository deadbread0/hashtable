#include "free_memory.h"

void DestroyTable(hashtable_type* hashtable)
{
    for (int i = 0; i < hashtable->size; i++)
    {
        hashtable_el_type* current_el = hashtable->hash_table[i].next_elem;
        hashtable_el_type* prev_el = hashtable->hash_table[i].next_elem;
        while (current_el)
        {
            prev_el = current_el;
            current_el = current_el->next_elem;
            free(prev_el);
        }
    }
    free(hashtable->hash_table);
}

void CleanMemory(char** arr_of_words, hashtable_type* hashtable)
{
    for (int i = 0; i < hashtable->num_of_words; i++)
        free(arr_of_words[i]);
        
    free(arr_of_words);
}

void DestroyBuf(char* buf)
{
    free(buf);
}