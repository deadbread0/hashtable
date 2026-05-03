#define TYPES

typedef unsigned int hashfunc_t(char* word);

enum list_err_t {
    NO_ERRORS,
    MEMORY_ALLOCATION,
    NULLPTR
};

static const int SIZE_OF_HASH_TABLE = 997; //достаточно большое простое число
static const int MAX_LEN_OF_WORD = 32;

struct hashtable_el_type {
    hashtable_el_type* next_elem; 
    char word[MAX_LEN_OF_WORD];
    unsigned int hash_num;
};

struct hashtable_type {
    hashtable_el_type* hash_table; 
    int size; //так называемый amount of backets
    int num_of_words; //всего слов
    hashfunc_t* func;
};

// struct list_t {
//     hashtable_type* data; //массив структур
//     int free;
//     int size;
//     int capacity;
//     int ht_size;
//     list_err_t error;
//     hashfunc_t* func;
// };

// struct some_list_el_t {
//     int hashnum;
//     int index;
// };

// struct more_list_el_t {
//     some_list_el_t* arr_of_el;
//     int size;
// };