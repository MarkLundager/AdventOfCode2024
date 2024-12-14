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
static unsigned long result_part_1;
static unsigned long result_part_2;


unsigned long add_with_overflow_check(unsigned long a, unsigned long b, unsigned long *result_part_1) {
    if (a > ULLONG_MAX - b) {
        return 1;
    }
    *result_part_1 = a + b;
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

bool recursion_part1(unsigned long target, node_t*tail, unsigned long value){
    if(tail->next == NULL){
        return (target == value + tail->value||target == value * tail->value);
    }
    return (recursion_part1(target,tail->next, value + tail->value) 
    || recursion_part1(target,tail->next, value * tail->value));
}

bool recursion_part2(unsigned long target, node_t*tail, unsigned long value){
    if(tail->next == NULL){
        return (target == value + tail->value||target == value * tail->value || target == new_operator(value, tail->value));
    }
    return (recursion_part2(target,tail->next, value + tail->value) 
    || recursion_part2(target,tail->next, value * tail->value) 
    || recursion_part2(target,tail->next, new_operator(value, tail->value)));
}

void check_valid_line(unsigned long target, node_t* head){
    if(head == NULL){
        printf("WOOOPS EMPTY?\n");
        return;
    }
    if(head->next == NULL){
        printf("ONLY ONE NUMBER!?\n");
        if(target == head->value){
            result_part_1 ++;
        }
        return;
    }
    if(recursion_part1(target, head->next, head->value)){
        add_with_overflow_check(result_part_1,target,&result_part_1);
    }
    if(recursion_part2(target, head->next, head->value)){
        add_with_overflow_check(result_part_2,target,&result_part_2);
    }
}


void process_line(FILE* file, unsigned long target){
    unsigned long number;
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, file);
    char* token = strtok(buffer, " ");
    node_t* head = NULL;
    while(token !=NULL){
        sscanf(token, "%lu",&number);
        append(&head,number);
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

void read_data_into_memory(){
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
    return 0;
}


int main(){
    if(READ){
        read_data(DAY);
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    read_data_into_memory();
    solve();
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_results(result_part_1, result_part_2);
}