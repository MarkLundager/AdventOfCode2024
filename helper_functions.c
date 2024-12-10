#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <errno.h>
#include "helper_functions.h"
#include <unistd.h> 
#include<stdbool.h>


int compare (const void *a, const void*b){
    return(*(int*)a - *(int*)b);
}
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
    return fwrite(buffer, size, nmemb, (FILE*)userp);
}
unsigned int hash_function(int key) {
    return key % HASHMAP_SIZE;
}

HashMapEntry_t* create_hash_map() {
    HashMapEntry_t *map = calloc(sizeof(HashMapEntry_t),HASHMAP_SIZE);
    return map;
}
int lookup_and_add(HashMapEntry_t *hash_map, int key, bool bool_add){
    int hashed_key = key % HASHMAP_SIZE;
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
void free_hashmap(HashMapEntry_t hashmap[], int size) {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        HashMapEntry_t* current = (&hashmap[i])->next;
        while (current != NULL) {
            HashMapEntry_t *next = current->next;
            free(current); 
            current = next; 
        }
    }
    free(hashmap);
}
void create_and_append(LinkedList_t* head, int data) {
    LinkedList_t* new_node = malloc(sizeof(LinkedList_t));
    new_node->snd = data;
    if (head == NULL) {
        head = new_node;
    } else {
        LinkedList_t* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
LinkedList_t ** create_linked_list(size_t size){
    LinkedList_t ** head = malloc(sizeof(LinkedList_t *) * size);
    if(head == NULL){
        perror("MALLOC FAILED");
    }
    for(int i = 0; i<size; i++){
        head[i] = NULL;
    }
    return head;
}