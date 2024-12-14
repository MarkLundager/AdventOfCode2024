#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#define LINE_SIZE (500)
#define DAY (2)
static int result_part_1 = 0;
static int result_part_2 = 0;

enum Direction{
    ASCENDING,
    DESCENDING,
    UNKNOWN
};

static bool first = true;
int direction = UNKNOWN;
static bool damp = false;



void reset(FILE* file, char c){
    first = true;
    direction = UNKNOWN;
    char temp_char;
    damp = false;
    if(c != '\n'){
        while(fscanf(file, "%c", &temp_char) == 1 && temp_char != '\n');
    }
}

int solve(){
    FILE* file = fopen(INPUT_FILE,"r");
    char c;
    int number = 0;

    int prev;
    int abs_value;
    int cmp_value;
    while(fscanf(file, "%c", &c) == 1){
        if(isdigit(c)){
            number = c - '0';
            while((fscanf(file, "%c", &c)) == 1 && isdigit(c)){
                 number = number * 10 + (c - '0');
            }
        }
        if(first){
            prev = number;
            first = false;
            continue;
        }
        cmp_value = number - prev;
        abs_value = abs(cmp_value);
        if(abs_value > 3 || abs_value == 0){
            if(damp){
                reset(file,c);
                continue;
            }
            else{
                damp = true;
                goto dampen;
            }
            return damp;
        }
        switch(direction){
            case UNKNOWN:
                direction = (cmp_value <0) ? DESCENDING : ASCENDING; // DESC
                break;
            case ASCENDING:
                if(cmp_value<0){
                    if(damp){
                        reset(file,c);
                        continue;
                    }
                    else{
                        damp = true;
                        goto dampen;
                    }
                }
                break;
            case DESCENDING:
                if(cmp_value>0){
                    if(damp){
                        reset(file,c);
                        continue;
                    }
                    else{
                        damp = true;
                        goto dampen;
                    }
                } 
                break;
        }
dampen:
        if(c == '\n'){
            if(!damp){
                result_part_1++;
            }
            result_part_2++;
            reset(file, c);
        }
        prev = number;
    }
    return 0;
}


int main(){
    if(READ){
        read_data(DAY);
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    solve();
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_results(result_part_1, result_part_2);
}