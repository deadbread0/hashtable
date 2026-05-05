#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <stdint.h>
#include <immintrin.h>
#pragma GCC push_options
#pragma GCC target("avx2")
#pragma GCC target("avx")

#ifndef TYPES
#include "types.h"
#endif

unsigned int Return0(char* word);
unsigned int FirstLetterOfWord(char* word);
unsigned int ReturnLenOfWord(char* word);
unsigned int ReturnASCIISum(char* word);
unsigned int RotateLeft(char* word);
int RoL(int a);
unsigned int crc32(char* word);
unsigned int crc32Optimized(char* word);
extern "C" unsigned int CRC32ASM(char* word);
