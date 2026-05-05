#include "output.h"

bool FillFileWithWords(FILE* output_file, char* buf, int bufsize) //bufsize это типа не считая \0, то, что возвращает GetSizeOfInputFile
{
    assert(output_file);
    assert(buf);
    char word[MAX_LEN_OF_WORD] = {};
    char* newbuf = (char*)calloc(bufsize, sizeof(char));

    int j = 0;
    for (int i = 0; i < bufsize;)
    {
        SkipNotLeller(buf, &i);

        while (isalpha(buf[i])) 
        {
            newbuf[j] = buf[i];
            j++;
            i++;
        }
        newbuf[j] = '\t';
        j++;
    }  

    newbuf[j + 1] = '\0';
    fwrite(newbuf, sizeof(char), j, output_file);
    free(newbuf);

    return true;
}

void SkipNotLeller(char* buf, int *i)
{
    assert(buf);
    assert(i);

    while (!isalpha(buf[*i])) 
        (*i) += 1;
}


void CSVoutput(hashtable_type* hashtable)
{
    assert(hashtable != nullptr);

    FILE* filee = fopen("files/data_for_statistics.csv", "w");
    fprintf(filee, "hashnum,amount\n");
    for (int i = 0; i < hashtable->size; i++)
    {
        int amount_of_words_in_backet = hashtable->hash_table[i].word ? 1 : 0; //подсчет количества слов в одной корзине
        hashtable_el_type* current_el = &hashtable->hash_table[i];
        while (current_el->next_elem) 
        {
            amount_of_words_in_backet++;
            current_el = current_el->next_elem;
            int index = hashtable->hash_table[i].hash_num % hashtable->size;
            fprintf(filee, "%d, %d\n", index, 1);
        }

    }

    fclose(filee);
}

void DumpHT(hashtable_type* hashtable, long long int time)
{
    FILE* dump_file = fopen(NAME_OF_INFO_FILE, "w");

    float variance = CountVariance(hashtable);
    float loadfactor = CountLoadFactor(hashtable);
    fprintf(stderr, "%ld\n", time);

    fprintf(dump_file,  "----------------------------------------\n"
                        "load factor: %f\n"
                        "variance: %f\n"
                        "CPU cycles: %lld\n"
                        "----------------------------------------\n", 
                        loadfactor, variance, time);

    for (int i = 0; i < hashtable->size; i++)
    {
        hashtable_el_type* current_el = &hashtable->hash_table[i];

        while (current_el) 
        {
            fprintf(dump_file, "[%d] hashnum: %u word: %s\n", i, current_el->hash_num, current_el->word);
            current_el = current_el->next_elem;
        }
    }

    fclose(dump_file);
}

float CountVariance(hashtable_type* hashtable)
{
    float variance = 0;
    int sum2 = 0;
    float loadfactor = CountLoadFactor(hashtable);

    for (int i = 0; i < hashtable->size; i++)
    {
        hashtable_el_type* current_el = &hashtable->hash_table[i];
        int backet_size = 0;

        while (current_el) 
        {
            backet_size++;
            current_el = current_el->next_elem;
        }

        variance += (loadfactor - (float) backet_size) * (loadfactor - (float) backet_size);
    }

    variance /= hashtable->num_of_words;

    return variance;
}

float CountLoadFactor(hashtable_type* hashtable) //средний размер подмножеств
{
    return (float) hashtable->num_of_words / hashtable->size;
}