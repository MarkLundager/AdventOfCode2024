#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <stdbool.h>
#include <time.h>
#define DOMAIN_URL ("https://adventofcode.com/2024/day/")
#define ENDPOINT ("/input")
#define INPUT_FILE ("input.txt")
#define MAX_URL_SIZE (500)
#define MAX_PATH_SIZE (500)


struct timespec start, end;

//STRUCTURES 
typedef struct Pos_t{
    int x;
    int y;
    struct Pos_t* next;
} Pos_t;

typedef struct node_t{
    unsigned long value;
    struct node_t* next;
} node_t;

typedef struct HashMapEntry_t{
    int key;
    int value;
    int init;
    struct HashMapEntry_t* next;
} HashMapEntry_t;



//Input retrieval
size_t read_data(unsigned short day);
size_t write_to_file(void *buffer, size_t size, size_t nmemb, void *userp);

//Solutions output
void print_results(unsigned long result1, unsigned long result2);


//-----------------data structures----------------

//Hashmap function
unsigned int hash_function(int key, size_t size);
int lookup_and_add(HashMapEntry_t hash_map[], int key, bool bool_add,size_t size);
HashMapEntry_t* create_hash_map(size_t size);
void free_hashmap(HashMapEntry_t hashmap[], size_t size);


//Linked list single value
void free_linked_list(node_t **head);
void swap(node_t** lhs, node_t **rhs);
void append(node_t** head, unsigned long data);

//Linked list 2d positions
void free_pos_list(Pos_t **head);
void swap_pos(Pos_t** lhs, Pos_t **rhs);
void append_pos(Pos_t** head, int x, int y);
void append_pos_unique(Pos_t** head, int x, int y);

//-----------DAY X HELPER FUNCTIONS----------------

//------------DAY 1 HELPER FUNCTIONS:
int compare(const void *a, const void*b);

//------------DAY 7 HELPER FUNCTIONS:
bool recursion_part1(unsigned long target, node_t*tail,unsigned long value);
bool recursion_part2(unsigned long target, node_t*tail,unsigned long value);