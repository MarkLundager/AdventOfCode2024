#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <errno.h>
#include "helper_functions.h"
#include <unistd.h> 
#include<stdbool.h>


size_t read_data(unsigned short day){
    // char path[MAX_PATH_SIZE];
    // snprintf(path, MAX_PATH_SIZE, "./day%d/%s",day,INPUT_FILE);
    FILE* file = fopen(INPUT_FILE, "w");
    if(file ==NULL){
        perror("Error opening file\n");
        printf("Error code: %d\n", errno);
        return -1;
    }  
    CURL *curl = curl_easy_init();
    char url[MAX_URL_SIZE];
    snprintf(url, sizeof(url), "%s%u%s",DOMAIN_URL,day,ENDPOINT);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_to_file);
    curl_easy_setopt(curl, CURLOPT_COOKIE, SESSIONID);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA, file);
    int success = curl_easy_perform(curl);
    if(success != CURLE_OK){
        perror("Error occured while retrieivng data with CURL");
    }
    curl_easy_cleanup(curl);
    fclose(file);
    return success;
}
size_t write_to_file(void *buffer, size_t size, size_t nmemb, void *userp){
    if (((char*)buffer)[size*nmemb - 1] == '\n') {
        fwrite(buffer, size, nmemb-1, (FILE*)userp);
    }
    else{
        fwrite(buffer, size, nmemb, (FILE*)userp);
    }
    return nmemb*size;
}

double get_time(struct timespec start, struct timespec end){
        double time_taken = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;
        return time_taken;
}

//print results with time.
void print_results(unsigned long result1, unsigned long result2){
    double time_taken = get_time(start, end);
    printf("Part 1 result:  %lu\n"
           "Part 2 result:  %lu\n"
           "Total Time:     %f seconds\n",
            result1,result2,time_taken);
}

void print_seperate_times(){
    double part1_time = get_time(start,end) - get_time(part2_time_s, part2_time_e);
    double part2_time = get_time(start,end) - get_time(part1_time_s, part1_time_e);
    printf("Part 1 time:    %f seconds\n",part1_time);
    printf("Part 2 time:    %f seconds\n",part2_time);

}



// HASHMAP functions:
unsigned int hash_function(int key, size_t size) {
    return key % size;
}
HashMapEntry_t* create_hash_map(size_t size) {
    HashMapEntry_t *map = calloc(sizeof(HashMapEntry_t), size);
    return map;
}
int lookup_and_add(HashMapEntry_t *hash_map, int key, bool bool_add, size_t size){
    int hashed_key = key % size;
    HashMapEntry_t* entry = &hash_map[hashed_key];
    while (entry){
        if(entry->init == false && bool_add){
            entry->init = true;
            entry->key = key;
            entry->value = 1;
            return entry->value;
        }
        if(entry->key == key){
            if(bool_add){
                entry->value++;
            }
            return entry->value;
        }
        if(entry->next == NULL){
            break;
        }
        entry = entry->next;
    }
    if(bool_add){
        HashMapEntry_t* temp_entry = malloc(sizeof(HashMapEntry_t));
        temp_entry->key = key;
        temp_entry->value = 1;
        temp_entry->next = NULL;
        temp_entry->init = true;
        entry->next = temp_entry;
        return temp_entry->value;
    }
    return 0;
}
void free_hashmap(HashMapEntry_t hashmap[], size_t size) {
    for (int i = 0; i < size; i++) {
        HashMapEntry_t* current = (&hashmap[i])->next;
        while (current != NULL) {
            HashMapEntry_t *next = current->next;
            free(current); 
            current = next; 
        }
    }
    free(hashmap);
}


void free_tree(tree_node_t* root) {
    if (root == NULL) {
        return;
    }
    
    free_tree(root->left);
    free_tree(root->right);
    
    free(root);
}


//Tree functions:
void split_tree_node(tree_node_t** tree_node, unsigned long first_child, unsigned long second_child){
    (*tree_node)->parent = true;
    (*tree_node)->left = create_tree_node(first_child, false);
    (*tree_node)->right = create_tree_node(second_child, false);
}

void append_root(tree_node_t **list, unsigned long value){
    tree_node_t* new_root = create_tree_node(value, false);
    if(*list == NULL){
        *list = new_root;
    }
    else{
        tree_node_t* current = *list;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_root;
    }
}

tree_node_t* create_tree_node(unsigned long value, bool parent){
    tree_node_t* new_tree_node = malloc(sizeof(*new_tree_node));
    if(new_tree_node != NULL){
        new_tree_node->next = NULL;
        new_tree_node->parent = parent;
        new_tree_node->left = NULL;
        new_tree_node->right = NULL;
        new_tree_node->value = value;
    }
    return new_tree_node;
}





// //Linked list single value functions:
void append(node_t **head, unsigned long number){
    node_t *new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
    new_node->value = number;

    if(*head == NULL){
        *head = new_node;
        return;
    }
    node_t* current = *head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new_node;
}
void free_linked_list(node_t **head) {
    node_t *current = *head;
    node_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void swap(node_t** lhs, node_t **rhs){
    int temp;
    temp = (*rhs)->value;
    (*rhs)->value = (*lhs)->value;
    (*lhs)->value = temp;
}



//Linked list 2d value
bool append_pos_unique(Pos_t **head, int x, int y){
    Pos_t *new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
    new_node->x = x;
    new_node->y = y;

    if(*head == NULL){
        *head = new_node;
        return true;
    }
    Pos_t* current = *head;
    while(current->next != NULL){
        if(current->x == x && current-> y == y){
            free(new_node);
            return false;
        }
        current = current->next;
    }
    if(current->x == x && current-> y == y){
        free(new_node);
        return false;
    }
    current->next = new_node;
    return true;
}

void append_pos(Pos_t **head, int x, int y){
    Pos_t *new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
    new_node->x = x;
    new_node->y = y;

    if(*head == NULL){
        *head = new_node;
        return;
    }
    Pos_t* current = *head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new_node;
}

void free_pos_list(Pos_t **head) {
    Pos_t *current = *head;
    Pos_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void swap_pos(Pos_t** lhs, Pos_t **rhs){
    int temp_x;
    int temp_y;
    temp_x = (*rhs)->x;
    temp_y = (*rhs)->y;
    (*rhs)->x = (*lhs)->x;
    (*rhs)->y = (*lhs)->y;
    (*lhs)->x = temp_x;
    (*lhs)->y = temp_y;
}

Pos_t*** create_pos_matrix(int size){
    Pos_t ***head = calloc(size, sizeof(*head));
    for(int i = 0; i<size; i++){
        head[i] = calloc(size, sizeof(*head[i]));
    }
    return head;
}
//          DAY X HELPER FUNCTIONS:


//DAY 1:
int compare (const void *a, const void*b){
    return(*(int*)a - *(int*)b);
}