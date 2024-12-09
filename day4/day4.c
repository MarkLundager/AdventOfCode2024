#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>

#define LINE_SIZE (140)
#define LINE_SIZE_EXTRACT (150)
#define WORD_LENGTH (4)
static int directions[8][2] = {
        {0, 1},  
        {0, -1}, 
        {1, 0},  
        {-1, 0}, 
        {1, 1},  
        {1, -1}, 
        {-1, 1}, 
        {-1, -1} 
    };
static int bullshit_directions[4][4] = {
        { -1,  -1,  -1,  1},
        {-1,  1,   1,   1},
        {1,   1,   1,   -1},
        { 1,   -1,  -1,   -1}
        };
static char xmas[] = "XMAS";
static int result;
static int result2;
char **matrix;

bool checkbounds(int i, int j){
    return (i >= 0 && i < LINE_SIZE && j >= 0 && j < LINE_SIZE);
}


void checkdumbshit(int i, int j){
    for(int k = 0; k<4; k++){
        if( matrix[i+bullshit_directions[k][0]][j+bullshit_directions[k][1]] == 'S'
            && matrix[i+bullshit_directions[k][2]][j+bullshit_directions[k][3]] == 'S'
            && matrix[i-bullshit_directions[k][0]][j-bullshit_directions[k][1]] == 'M'
            && matrix[i-bullshit_directions[k][2]][j-bullshit_directions[k][3]] == 'M')
            {
                result2 ++;
            }
    }
}

void check(int i, int j, int di, int dj){
    for(int k = 0; k<WORD_LENGTH; k++){  //why the fck am I not using x,y ?
        int ni = i + k * di;
        int nj = j + k * dj;
        if(!checkbounds(ni,nj) || matrix[ni][nj] != xmas[k]){
            return;
        }
    }
    result++;
}
int solve(){
    FILE* file = fopen(INPUT_FILE,"r");
    matrix = malloc(LINE_SIZE * sizeof(*matrix));
    for(int i = 0; i<LINE_SIZE; i++){
        matrix[i] = malloc(LINE_SIZE);
    }
    for(int i = 0; i<LINE_SIZE; i++){
        fgets(matrix[i], LINE_SIZE_EXTRACT, file);
    }

    for(int i = 0; i <LINE_SIZE; i++){
        for(int j = 0; j<LINE_SIZE; j++){
            for(int k = 0; k<8; k++){
                if(matrix[i][j] == 'X'){
                    check(i,j,directions[k][0],directions[k][1]);
                }
            }
            if(matrix[i][j] == 'A'){
                if(i >0 && i < LINE_SIZE -1 && j >0 && j < LINE_SIZE -1){
                    checkdumbshit(i,j);
                }
            }
        }
    }
    for(int i = 0; i<LINE_SIZE; i++){
        free(matrix[i]);
    }
    free(matrix);
    printf("Part 1 result: %d\n", result);
    printf("Part 2 result: %d\n", result2);
    return 0;
}


int main(){
    read_data(4);
    solve();
}