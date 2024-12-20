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
#define READ (0)


struct timespec start, end;
struct timespec part1_time_s,part1_time_e,part2_time_s,part2_time_e;
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


typedef struct tree_node_t{
    bool parent;
    unsigned long value;
    struct tree_node_t* next;
    struct tree_node_t* left;
    struct tree_node_t* right;
}tree_node_t;


//Input retrieval
size_t read_data(unsigned short day);
size_t write_to_file(void *buffer, size_t size, size_t nmemb, void *userp);

//Output functions
double get_time(struct timespec start, struct timespec end);
void print_results(unsigned long result1, unsigned long result2);
void print_seperate_times();


//-----------------data structures----------------

//TREES (WE LOVE EM)
tree_node_t* create_tree_node(unsigned long value, bool parent);
void split_tree_node(tree_node_t** tree_node, unsigned long first_child, unsigned long second_child);
void append_root(tree_node_t **list, unsigned long value);
void free_tree(tree_node_t* root);

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
bool append_pos_unique(Pos_t** head, int x, int y);
Pos_t*** create_pos_matrix(int size);

//-----------DAY X HELPER FUNCTIONS----------------

//------------DAY 1 HELPER FUNCTIONS:
int compare(const void *a, const void*b);

//------------DAY 7 HELPER FUNCTIONS:
bool recursion_part1(unsigned long target, node_t*tail,unsigned long value);
bool recursion_part2(unsigned long target, node_t*tail,unsigned long value);