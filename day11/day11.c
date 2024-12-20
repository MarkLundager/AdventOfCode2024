#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define DAY (11)
#define BUFFER_SIZE (500)
#define STONE_MULTIPLIER (2024)
#define BLINKS (75)
static long result_part_1;
static long result_part_2;
static int current_blink;
node_t* stones;

void read_data_into_memory(){
    FILE* file = fopen(INPUT_FILE, "r");
    if(file == NULL){
        perror("Failed to open file");
        return;
    }
    char buffer[500];
    if(fgets(buffer, BUFFER_SIZE, file) == NULL){
        perror("Could not read from file");
        fclose(file);
        return;
    }
    char *token = strtok(buffer, " ");
    int number;
    while(token != NULL){
        sscanf(token, "%d", &number);
        append(&stones, number);
        result_part_1 ++;
        token = strtok(NULL, " ");
    }
    fclose(file);
    return;
}



int count_digits(unsigned long value){
    int count = 0;
    //dont have to check for zero as it is already handled in transform stone.
    while(value >0){
        value = value / 10;
        count ++;
    }
    return count;
}

void split_number(unsigned long number, unsigned long* first_half, unsigned long* second_half, int n_digits) {
    int split_factor = pow(10, n_digits / 2);  

    *second_half = number % split_factor;        
    *first_half = number / split_factor;         
}

void transform_stone(node_t** stone){
    unsigned long stone_value = (*stone)->value;
    if(stone_value == 0){
        (*stone)->value = 1;
        return;
    }
    int nbr_digits = count_digits(stone_value);
    if(nbr_digits%2 == 0){
        unsigned long left;
        unsigned long right;
        split_number(stone_value, &left, &right, nbr_digits);
        split_tree_node(stone, left,right);
        result_part_1 ++;
        return;
    }
    (*stone)->value = stone_value * STONE_MULTIPLIER;
}


void solve(){
    for(int i = 0; i<BLINKS; i++){
        node_t* current_stone = stones;
        while(current_stone != NULL){
            transform_stone(&current_stone);
            current_blink ++;
            current_stone = current_stone->next;
        }
    }

     free_tree(&current_stone);


    return;
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