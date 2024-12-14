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
#define MAX_FILE_SIZE (9)
static long result_part_1;
static long result_part_2;
bool occupied;
static int index_reversed;
static int index_normal;
static int file_index_reversed;
static char * buffer;
static int file_size_reversed;
static int new_index;


void append_reverse_part2(int free_space){
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
}

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



void read_data_into_memory(){
    int file_size = 0;
    int free_space = 0;
    int file_index = 0;
    FILE* file = fopen(INPUT_FILE,"r");

    buffer = malloc(MAX_BUFFER_SIZE);
    fgets(buffer, MAX_BUFFER_SIZE, file);
    if(buffer == NULL){
        perror("Input too large\n");
    }
    int buffer_length = strlen(buffer);
    file_index_reversed = (strlen(buffer)/2);
    index_reversed = strlen(buffer)-1;
    file_size_reversed = buffer[index_reversed] - '0';
    while (index_normal<buffer_length && index_normal < index_reversed){

        file_size = buffer[index_normal] - '0';

        for(int i = 0; i < file_size; i++){
            result_part_1 += new_index * file_index;
            result_part_2 += new_index * file_index;
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
    free(buffer);
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