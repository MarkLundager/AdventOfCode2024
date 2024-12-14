#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#define DAY (9)
#define MAX_BUFFER_SIZE (32000)

static long result_part_1;
static long result_part_2;
static char* buffer;

static int index_normal;
static int index_reversed;

static int file_index;
static int file_index_reversed;

static int file_size;
static int file_size_reversed;

static int new_index;
static bool* dictionary;

void reset_part2(){
    file_index_reversed =  (strlen(buffer)/2);
    index_reversed = strlen(buffer)-1;
    file_size_reversed = buffer[index_reversed] - '0';
}
//Compared to part 1, we have to keep track of which files we've already appended. Hence, make a dictionary to look up the file index.
//then iterate from last file index to the index we're currently at and see if we can see a file with space equal to free space.
void append_reverse_part2(int free_space){
    while(index_reversed > index_normal && free_space){

        file_size_reversed = buffer[index_reversed] - '0';
        if(file_size_reversed <= free_space && dictionary[file_index_reversed] == 0){
            dictionary[file_index_reversed] = 1;
            for(int i = 0; i<file_size_reversed; i++){
                result_part_2 += file_index_reversed * new_index; 
                new_index ++;
                free_space --;
            }
        }

        file_index_reversed --;
        index_reversed = index_reversed - 2;
    }
    while(free_space){
        new_index ++;
        free_space --;
    }

    reset_part2();
}

//while free space, we insert the current file we're at. if we run out before free_space is done, that's fine, then
//we just iterate to next file and continue appending. If free_space runs out, then we just stop and next time this
//function is called we just resume where we left off.
void append_reverse(int free_space, bool last){
    while(free_space && index_reversed > index_normal){
        if(file_size_reversed>0){
            result_part_1 += new_index * file_index_reversed;
            new_index ++;
            file_size_reversed--;
            free_space --;
        }
        else{
            index_reversed = index_reversed - 2;
            file_size_reversed = buffer[index_reversed] -'0';
            file_index_reversed --;
        }
    }
    while(file_size_reversed && last){
        result_part_1 += new_index * file_index_reversed;
        new_index ++;
        file_size_reversed--;
    }
}


//Just read everything into a buffer
void read_data_into_memory(){
    FILE* file = fopen(INPUT_FILE,"r");
    buffer = malloc(MAX_BUFFER_SIZE);
    fgets(buffer, MAX_BUFFER_SIZE, file);

    if(buffer == NULL){
        perror("Input too large\n");
    }
    fclose(file);
    return;
}

//Create variables for position index, file index, and file size so we can go from left to right and right to left at the same time.
//When we find free space, we call on either part 1 or part 2 to insert an eligible file from the right.
int solve(){
    int free_space = 0;
    int buffer_length = strlen(buffer);
    file_index_reversed =  (strlen(buffer)/2);
    index_reversed  = strlen(buffer)-1;
    file_size_reversed = buffer[index_reversed] - '0';

    while (index_normal<buffer_length && index_normal < index_reversed){
        file_size = buffer[index_normal] - '0';
        for(int i = 0; i < file_size; i++){
            result_part_1 += new_index * file_index;
            new_index ++;
        }
        index_normal ++;
        free_space = buffer[index_normal] -'0';
        if(free_space>0){
            append_reverse(free_space, false);
        }
        index_normal ++;
        file_index++;
        if(index_normal == index_reversed){
            append_reverse(0, true);
        }
    }
    return 0;
}

int solve_part_2(){
    file_index =0;
    index_normal =0;
    file_size = 0;
    new_index = 0;
    int free_space = 0;
    int buffer_length = strlen(buffer);
    file_index_reversed =  (strlen(buffer)/2);
    index_reversed = strlen(buffer)-1;
    file_size_reversed = buffer[index_reversed] - '0';
    dictionary = calloc(sizeof(*dictionary), file_index_reversed+1);


    while (index_normal<buffer_length && index_normal < index_reversed){
        file_size = buffer[index_normal] - '0';
        while(dictionary[file_index] == 1 && file_size){
            new_index ++;
            file_size --;
        }
        while(file_size && dictionary[file_index] == 0){
            result_part_2 += new_index * file_index;
            new_index ++;
            file_size --;
        }
        index_normal ++;
        free_space = buffer[index_normal] -'0';
        if(free_space>0){
            append_reverse_part2(free_space);
        }
        index_normal ++;
        file_index++;
    }
    return 0;
}


int main(){
    if(READ){
        read_data(DAY);
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    read_data_into_memory();
    clock_gettime(CLOCK_MONOTONIC, &part1_time_s);
    solve();
    clock_gettime(CLOCK_MONOTONIC, &part1_time_e);
    clock_gettime(CLOCK_MONOTONIC, &part2_time_s);
    solve_part_2();
    clock_gettime(CLOCK_MONOTONIC, &part2_time_e);
    free(buffer);
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_results(result_part_1, result_part_2);
    print_seperate_times();
}