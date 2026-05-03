#include "list_functions.h"
#include <cstring>
#include <ctype.h>

extern "C" int MyOwnStrncmp(char* word1, char* word2);

void FillHashTable(hashtable_type* hashtable, char* word, unsigned int hashnum) //возвращает 1, если слово было добавлено в хт
{
    assert(hashtable != nullptr);
    assert(word != nullptr);

    unsigned int index = hashnum % hashtable->size; //рассчет индекса слова в хт

    if (hashtable->hash_table[index].word[0]) //если по индексу уже что то есть
    {
        hashtable_el_type* current_el = &hashtable->hash_table[index];
        hashtable_el_type* prev_el = &hashtable->hash_table[index];
        int flag = 0;
        
        while (current_el) //current_el->next
        {
            if (!MyStrcmp(word, current_el->word))
                return;

            prev_el = current_el;
            current_el = current_el->next_elem;
            flag = 1;
        }

        hashtable_el_type* new_elem = (hashtable_el_type*)calloc(1, sizeof(hashtable_el_type));
        memcpy(&(new_elem->word), word, strlen(word));
        new_elem->hash_num = hashnum;
        new_elem->next_elem = nullptr;
        hashtable->num_of_words++;

        if (flag)
        {
            prev_el->next_elem = new_elem;
            return;
        }

        hashtable->hash_table[index].next_elem = new_elem; //current_el->next_elem
        return;
        
    } 

    hashtable->num_of_words++;
    hashtable->hash_table[index].hash_num = hashnum;
    hashtable->hash_table[index].next_elem = nullptr;
    memcpy(&(hashtable->hash_table[index].word), word, strlen(word)); //попробовать 32
}


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

int FindSomeElementsInTable(hashtable_type* hashtable, char** words)
{
    int amount_of_found_words = 0, amount_of_words = hashtable->num_of_words;
    for (int i = 0; i < amount_of_words; i++)
    {
        if (!words[i])
            continue;

        if (FindOneElInTable(hashtable, words[i]))
            amount_of_found_words++; 
    }

    return amount_of_found_words;
}

hashtable_el_type* FindOneElInTable(hashtable_type* hashtable, char* word)
{
    unsigned int index = hashtable->func(word) % hashtable->size;
    hashtable_el_type* current_el = &hashtable->hash_table[index];

    while (current_el) 
    {
        // fprintf(stderr, "%s %s\n", word, current_el->word);
        if (current_el->word == nullptr) 
            printf("DEBUG: Found NULL pointer in FindOneElInTable\n");
       
        if (!MyStrcmp(word, current_el->word)) //нет доступа к этой памяти
            return current_el;

        current_el = current_el->next_elem;
    }

    return nullptr;
}

char** MakeArrOfWordsFromOneBuf(char* buf, int bufsize) //слова разделены табуляцией
{
    char** arr_of_words = (char**)calloc(bufsize, sizeof(char*));
    int c = 0;

    for (int i = 0; c < bufsize;)
    {
        SkipNotLeller(buf, &i);
        char* newbuf = (char*)calloc(1, MAX_LEN_OF_WORD);
        int j = 0;

        while (isalpha(buf[i])) 
        {
            newbuf[j] = buf[i];
            j++;
            i++;
        }

        newbuf[j] = '\0';
        arr_of_words[c] = newbuf;
        c++;
    }  

    return arr_of_words;
}

int MyStrcmp(char* word1, char* word2)
{
    int result = 0;

//     Program received signal SIGSEGV, Segmentation fault.
// 0x000000000040232d in MyStrcmp (word2=0x6c000000000057bb <error: Cannot access memory at address 0x6c000000000057bb>, word1=0x5aad30 "Potter")
//     at list_functions.cpp:149

// причем в функции FillHashTable уже используется MyStrcmp раньше, проходится по тем же элементам, а тут что-то идет не так..

// ==24730== LEAK SUMMARY: это на момент сегфолта
// ==24730==    definitely lost: 0 bytes in 0 blocks
// ==24730==    indirectly lost: 0 bytes in 0 blocks
// ==24730==      possibly lost: 0 bytes in 0 blocks
// ==24730==    still reachable: 10,015,995 bytes in 58,203 blocks
// ==24730==         suppressed: 0 bytes in 0 blocks


__asm__ 
(
    ".intel_syntax noprefix\n\t"

    "vmovups ymm0, [%1]\n\t"   
    "vmovups ymm1, [%2]\n\t"      
    "vptest  ymm0, ymm1\n\t"      
    "setnb al\n\t"
    "mov %0, eax\n\t"

    ".att_syntax prefix\n\t"
    :"+&r"(result)                     // список выходных параметров.
    :"r"(word1), "r"(word2)              // список входных параметров.
    :"ymm0", "ymm1"                      // список разрушаемых регистров.
);
return result;
}

