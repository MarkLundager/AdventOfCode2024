#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define DAY (8)
#define ASCII_TABLE_SIZE (128)
Pos_t** antennas;
static int row;
static int col;
static long result;
static long result2;


bool check_bound(int x, int y){
    return (x < row && x >= 0 && y < col && y >= 0);
}

void find_antinodes(int i, bool ***arrarr, bool result2){
    Pos_t * current_node = antennas[i];
    int current_node_x;
    int current_node_y;

    while(current_node != NULL){
        current_node_x = current_node->x;
        current_node_y = current_node->y;

        Pos_t* comparing_node = antennas[i];
        while(comparing_node != NULL){
            if(!(comparing_node->x == current_node_x && comparing_node->y == current_node_y)){
                int diff_x = current_node_x - comparing_node->x;
                int diff_y = current_node_y - comparing_node->y;
                int antinode_x = diff_x + current_node_x;
                int antinode_y = diff_y + current_node_y;

                if(check_bound(antinode_x, antinode_y)){
                    (*arrarr)[antinode_x][antinode_y] = true;
                }
                if(result2){
                    (*arrarr)[current_node_x][current_node_y] = true;
                }
                while(check_bound(antinode_x+diff_x, antinode_y+diff_y) && result2){
                    antinode_x += diff_x;
                    antinode_y += diff_y;
                    (*arrarr)[antinode_x][antinode_y] = true;
                }
            }
            comparing_node = comparing_node->next;
        }
        current_node = current_node->next;
    }
}


void read_data_into_memory(int day){
    read_data(day);
    antennas = malloc(sizeof(*antennas) * ASCII_TABLE_SIZE);
    for(int i = 0; i<ASCII_TABLE_SIZE; i++){
        antennas[i] = NULL;
    }

    int c;
    FILE* file = fopen(INPUT_FILE,"r");

    while ((c = fgetc(file)) != EOF){
        switch(c){
            case '\n':
                row++;
                col = 0;
                break;
            case '.':
                col ++;
                break;
            default: 
                append_pos(&antennas[c], row, col);
                col++;
                break;
        }
    }
    row++;
    fclose(file);
    return;
}

int solve(){
    bool **arrarr = malloc(row * sizeof(*arrarr));  //Malloc should work here as it should get initalised to 0 in second call.
    for(int i = 0; i<row; i++){
        arrarr[i] = calloc(col, sizeof(*arrarr[i]));
    }
    for(int i = 0; i<ASCII_TABLE_SIZE; i++){
        if(antennas[i] != NULL){
            find_antinodes(i, &arrarr,false);
        }
    }
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if(arrarr[i][j]){
                result ++;
            } 
        }
    }
    for(int i = 0; i<ASCII_TABLE_SIZE; i++){
        if(antennas[i] != NULL){
            find_antinodes(i, &arrarr,true);
        }
    }
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if(arrarr[i][j]){
                result2 ++;
            } 
        }
    }
    printf("Part 1 result: %ld\n", result);
    printf("Part 2 result: %ld\n", result2);
    return 0;
}


int main(){
    read_data_into_memory(DAY);
    return solve();
}