#include "list_functions.h"

extern "C" int MyOwnStrcmp(char* word1, char* word2);

void FillHashTable(hashtable_type* hashtable, char* word, unsigned int hashnum) 
{
    assert(hashtable != nullptr);
    assert(word != nullptr);

    unsigned int index = hashnum % hashtable->size; //рассчет индекса слова в хт

    if (hashtable->hash_table[index].word[0]) //если по индексу уже что то есть
    {
        hashtable_el_type* current_el = &hashtable->hash_table[index];
        hashtable_el_type* prev_el = &hashtable->hash_table[index];
        int flag = 0;
        
        while (current_el) 
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

        hashtable->hash_table[index].next_elem = new_elem; 
        return;
        
    } 

    hashtable->num_of_words++;
    hashtable->hash_table[index].hash_num = hashnum;
    hashtable->hash_table[index].next_elem = nullptr;
    memcpy(&(hashtable->hash_table[index].word), word, strlen(word)); 
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
        if (!MyStrcmp(word, current_el->word)) 
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

__asm__ 
(
    ".intel_syntax noprefix\n\t"

    "xor rax, rax\n\t"
    "vmovups ymm0, [%1]\n\t"   
    "vmovups ymm1, [%2]\n\t"  
    "vpxor ymm2, ymm0, ymm1\n\t"     
    "vptest  ymm2, ymm2\n\t"      
    "setnz al\n\t"
    "mov %0, eax\n\t"

    ".att_syntax prefix\n\t"
    :"+&r"(result)                     //список выходных параметров.
    :"r"(word1), "r"(word2)            //список входных параметров.
    :"ymm0", "ymm1", "rax"             //список разрушаемых регистров.
);

return result;
}


