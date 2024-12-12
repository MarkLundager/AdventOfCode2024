#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#define LINE_SIZE (500)


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
    int safe_reports = 0;
    int safe_reports_dampen = 0;
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
                safe_reports++;
            }
            safe_reports_dampen++;
            reset(file, c);
        }
        prev = number;
    }
    printf("Part 1 result: %d\n", safe_reports);
    printf("Part 2 result: %d\n", safe_reports_dampen);
    return 0;
}


int main(){
    read_data(2);
    solve();
}