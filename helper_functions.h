#include <stdio.h>
#include "config.h"
#include<stdbool.h>
#define DOMAIN_URL ("https://adventofcode.com/2024/day/")
#define ENDPOINT ("/input")
#define INPUT_FILE ("input.txt")
#define MAX_URL_SIZE (500)
#define MAX_PATH_SIZE (500)
#define HASHMAP_SIZE (1000)


enum Direction{
    ASCENDING,
    DESCENDING,
    UNKNOWN
};

typedef struct LinkedList_t{
    int value;
    struct LinkedList_t* next;
}LinkedList_t;

typedef struct HashMapEntry_t{
    int key;
    int value;
    int init;
    struct HashMapEntry_t* next;
} HashMapEntry_t;

//data structures
unsigned int hash_function(int key);
int lookup_and_add(HashMapEntry_t hash_map[], int key, bool bool_add);
HashMapEntry_t* create_hash_map();
void free_hashmap(HashMapEntry_t hashmap[], int size);


void free_linked_list(LinkedList_t **head);
void create_and_append(LinkedList_t** head, int data);

int compare(const void *a, const void*b);

//data handling
size_t read_data(unsigned short day);
size_t write_to_file(void *buffer, size_t size, size_t nmemb, void *userp);
LinkedList_t ** create_linked_list(size_t size);