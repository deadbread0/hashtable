#include "input.h"

int GetSizeOfInputFile(const char* filee_name)
{
    assert(filee_name != nullptr);

    struct stat StructStat;
    stat(filee_name, &StructStat);
    return StructStat.st_size;
}

int ReadText(FILE* filee, char* buf, int size) //записывает в buf все из файла до \0
{
    assert(buf != nullptr);
    assert(filee != nullptr);
 
    int amount_of_symb = fread(buf, sizeof(char), size, filee);
    buf[size] = '\0';
    return amount_of_symb;
}

void InputFromFile(const char* filee_name, hashtable_type* hashtable) 
{
    assert(filee_name != nullptr);
    assert(hashtable != nullptr);

    FILE* filee = fopen(filee_name, "r");
    char ch = 0; 
    int amount_of_words = 0;
    
    while (ch != EOF)
    {
        char buf[MAX_LEN_OF_WORD] = {};
        int i = 0;
        ch = fgetc(filee);

        while (ch != '\t' && ch != EOF)
        {
            buf[i] = ch;
            ch = fgetc(filee);
            i++;
        }

        buf[i] = '\0';

        unsigned int hashnum = hashtable->func(buf); 
        FillHashTable(hashtable, buf, hashnum); 
    }

}

