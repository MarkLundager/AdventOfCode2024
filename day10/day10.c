#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#define SIZE (42)
#define DAY (10)
static long result_part_1;
static long result_part_2;

static int **arrarr;
static Pos_t *** found_hikes;

static int directions[4][2] = {{0,1}, {1,0}, {0,-1},{-1,0}};

bool check_bounds(int row, int col){
    return (row >=0 && col>=0 && row < SIZE && col < SIZE);
}


void recursion(int row, int col, int step, int trail_head_row, int trail_head_col){
    step ++;
    if(step == 10){
       if(append_pos_unique(&found_hikes[trail_head_row][trail_head_col],row, col)){
        result_part_1 ++;
       }
       result_part_2 ++;
       return;
    }
    for(int i = 0; i<4; i++){
        int drow = directions[i][0];
        int dcol = directions[i][1];
        if(check_bounds(row+drow,col+dcol) &&arrarr[row+drow][col+dcol] == step){
            recursion(row+drow, col+dcol, step, trail_head_row,trail_head_col);
        }
    }
}


void check_score(int row,int col){
    int step = 1;
    for(int i = 0; i<4; i++){
        int drow = directions[i][0];
        int dcol = directions[i][1];
        if(check_bounds(row+drow,col+dcol) && arrarr[row+drow][col+dcol] == step){
            recursion(row+drow, col+dcol, step, row,col);
        }
    }
}

void solve(){
    for(int i = 0; i<SIZE; i++){
        for(int j= 0; j<SIZE; j++){
            if(arrarr[i][j] == 0){
                check_score(i, j);   
            }
        }
    }

    for(int j= 0; j<SIZE; j++){
        free(arrarr[j]);
    }
    free(arrarr);
    for(int i = 0; i<SIZE; i++){
        for(int j= 0; j<SIZE; j++){
            free_pos_list(&found_hikes[i][j]);
        }
    }
}

void read_data_into_memory(){
    FILE* file = fopen(INPUT_FILE, "r");
    arrarr = malloc(sizeof(*arrarr) * SIZE);
    for(int i = 0; i< SIZE; i++){
        arrarr[i] = malloc(sizeof(*arrarr[i]) * SIZE);
    }
    found_hikes = create_pos_matrix(SIZE);

    int row = 0;
    int col = 0;
    int c;

    while((c = fgetc(file)) != EOF){
        if(c == '\n'){
            row ++;
            col = 0;
            continue;
        } 
        arrarr[row][col] = c - '0';
        col ++;
    }
    fclose(file);
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