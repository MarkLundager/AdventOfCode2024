#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define DAY (7)
#define BUFFER_SIZE (5000)
static unsigned long result;
static unsigned long result2;


unsigned long add_with_overflow_check(unsigned long a, unsigned long b, unsigned long *result) {
    if (a > ULLONG_MAX - b) {
        return 1;
    }
    *result = a + b;
    return 0;
}

unsigned long new_operator(unsigned long a, unsigned long b){
    char temp[100];
    unsigned long new;
    snprintf(temp, sizeof(temp), "%lu",a);
    snprintf(temp+strlen(temp), sizeof(temp)-strlen(temp), "%lu",b);
    sscanf(temp, "%lu",&new);
    return(new);
}

void free_node(node_t** head){
    node_t* temp;
    while(*head!=NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
bool recursion(unsigned long target, node_t*tail, unsigned long value){
    if(tail->next == NULL){
        return (target == value + tail->value||target == value * tail->value || target == new_operator(value, tail->value));
    }
    return (recursion(target,tail->next, value + tail->value) 
    || recursion(target,tail->next, value * tail->value) 
    || recursion(target,tail->next, new_operator(value, tail->value)));
}

void check_valid_line(unsigned long target, node_t* head){
    if(head == NULL){
        printf("WOOOPS EMPTY?\n");
        return;
    }
    if(head->next == NULL){
        printf("ONLY ONE NUMBER!?\n");
        if(target == head->value){
            result ++;
        }
        return;
    }
    if(recursion(target, head->next, head->value)){
        add_with_overflow_check(result,target,&result);
    }

        
}

void append_number(unsigned long number, node_t **head){
    node_t *new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
    new_node->value = number;
    node_t* current = *head;
    if(*head == NULL){
        *head = new_node;
        return;
    }
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new_node;
}


void process_line(FILE* file, unsigned long target){
    unsigned long number;
    char buffer[BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, file);

    char* token = strtok(buffer, " ");
    node_t* head = NULL;
    while(token !=NULL){
        sscanf(token, "%lu",&number);
        append_number(number, &head);
        token = strtok(NULL, " ");
    }
    check_valid_line(target, head);
    free_node(&head);
}

unsigned long get_number(FILE* file, char nbr){
    char c;
    unsigned long number = (nbr-'0');
    while((c = fgetc(file)) != EOF && isdigit(c) && c != '\n'){
            number = number * 10 + (c - '0'); 
    }
    return number;
}

void read_data_into_memory(int day){
    read_data(day);
    char c;
    FILE* file = fopen(INPUT_FILE,"r");

    while ((c = fgetc(file)) != EOF){
        if(isdigit(c)){
            unsigned long target = get_number(file,c);
            process_line(file, target);
        }  
    }
    fclose(file);
    return;
}

int solve(){
    printf("Part 1 result: %lu\n", result);
    printf("Part 2 result: %lu\n", result2);
    return 0;
}


int main(){
    read_data_into_memory(DAY);
    solve();
}