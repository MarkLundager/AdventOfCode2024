#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#define HASHMAP_SIZE (1000)
#define NBR_ARRAYS (2)
#define ARRAY_SIZE (1000)
static int** arrarr;
static HashMapEntry_t* map; 

int solve(){
    map = create_hash_map(HASHMAP_SIZE);
    arrarr = malloc(NBR_ARRAYS * sizeof(int*));
    int counter = 0;
    long result_part_1 = 0;
    long result_part_2 = 0;
    int values[NBR_ARRAYS] = {0};

    for(int i = 0; i<NBR_ARRAYS; i++){
        arrarr[i] = malloc(ARRAY_SIZE*(sizeof(*arrarr[i])));
    }
    FILE* file = fopen(INPUT_FILE, "r");
    if(!file){
        perror("Failed to open file");
        return 1;
    } 
    while(fscanf(file, "%d", &arrarr[counter][values[counter]]) == 1){
        if(counter%NBR_ARRAYS == 1){
            lookup_and_add(map,arrarr[counter][values[counter]], true, HASHMAP_SIZE);
        }
        values[counter] ++;
        counter ++;
        counter = counter % NBR_ARRAYS;

    }
    fclose(file);
    for(int i =0; i<NBR_ARRAYS; i++){
        qsort(arrarr[i],values[i], sizeof(int), compare);
    }
    for(int i = 0; i<values[0]; i++){
        result_part_1 += abs(arrarr[0][i] - arrarr[1][i]);
        result_part_2 += (arrarr[0][i] * lookup_and_add(map, arrarr[0][i], false, HASHMAP_SIZE));
    }
    printf("Part 1 result: %ld\n", result_part_1);
    printf("Part 2 result: %ld\n", result_part_2);
    free_hashmap(map, HASHMAP_SIZE);
    for(int i = 0; i<NBR_ARRAYS; i++){
        free(arrarr[i]);
    }
    free(arrarr);
    return 0;
}
int main(){
    read_data(1);
    solve();
}