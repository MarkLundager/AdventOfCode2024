#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define DAY (8)
#define BUFFER_SIZE (5000)
#define ASCII_TABLE_SIZE (128)
node_t* antennas;
static long result;
static long result2;




void read_data_into_memory(int day){
    // read_data(day);
    antennas = malloc(sizeof(node_t) * ASCII_TABLE_SIZE);
    char c;
    FILE* file = fopen(INPUT_FILE,"r");

    while ((c = fgetc(file)) != EOF){
        if(isdigit(c)){
        }  
    }
    fclose(file);
    return;
}

int solve(){
    printf("Part 1 result: %ld\n", result);
    printf("Part 2 result: %ld\n", result2);
    return 0;
}


int main(){
    read_data_into_memory(DAY);
    solve();
}