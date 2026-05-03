#include "hash_functions.h"
#include <immintrin.h>
#pragma GCC push_options
#pragma GCC target("avx2")
#pragma GCC target("avx")

unsigned int Return0(char* word)
{
    assert(word != nullptr);
    return 0;
}

unsigned int FirstLetterOfWord(char* word)
{
    assert(word != nullptr);
    return word[0];
}

unsigned int ReturnLenOfWord(char* word)
{
    assert(word != nullptr);
    return strlen(word);
}

unsigned int ReturnASCIISum(char* word)
{
    assert(word != nullptr);

    int sum = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
        sum += word[i];

    return sum;
}

unsigned int RotateLeft(char* word)
{
    assert(word != nullptr);

    int h = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
        h = RoL(h) ^ word[i];

    return h;
}

int RoL(int a) //циклический сдвиг влево
{
      int t1, t2;

      t1 = a << 1;   //двигаем а вправо на n бит, теряя старшие биты
      t2 = a >> 31; //перегоняем старшие биты в младшие

      return t1 | t2;  //объединяем старшие и младшие биты
}

unsigned int crc32(char* word)
{
    assert(word != nullptr);

    unsigned int crc = 0xffffffff;
    int poly = 0xedb88320;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        int c = (crc ^ word[i]) & 0xff;
        for (int k = 0; k < 8; k++)
            c = (c & 1) != 0 ? poly ^ (c >> 1) : c >> 1;
        crc = c ^ (crc >> 8);
    }

    return crc ^ 0xffffffff;
}

unsigned int crc32Optimized(char* word)
{
    assert(word != nullptr);
    uint64_t crc = 0xffffffff;

    for (int i = 0; i < MAX_LEN_OF_WORD / 8; i++)
        crc = _mm_crc32_u64(crc, *((uint64_t*)word + i)); //0-7 символы

    return (uint32_t)crc;
}