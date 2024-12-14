#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#define DAY (3)

static char mul_string[] = "mul(,)";
static char dont_string[] = "don't()";
static char do_string[] = "do()";
static bool dont = false;
static int lhs;
static int rhs;
static long result_part_1;
static long result_part_2;

int get_number(FILE* file){
    char c;
    int number = 0;
    while((c = fgetc(file)) != EOF && isdigit(c)){
            number = number * 10 + (c - '0');
    }
    ungetc(c, file);
    return number;
}

void check_dont(FILE* file){
    int i = 1;
    char c;
    while ((c = fgetc(file)) != EOF && c == dont_string[i]){
        i++;
        if(c == ')'){
            dont = true;
        }
    }
    ungetc(c,file);
}

void check_do(FILE* file){
    int i = 1;
    char c;
    while ((c = fgetc(file)) != EOF && c == do_string[i]){
        i++;
        if(c == ')'){
            dont = false;
        }
    }
    ungetc(c,file);
}

void check_mul(FILE* file){
    int i = 1;
    char c;
    while ((c = fgetc(file)) != EOF && c == mul_string[i]){
        i++;
        switch (c){
            case '(':
                if(!((lhs = get_number(file)) > 0)){
                    return;
                }
                break;
            case ',':
                if(!((rhs = get_number(file)) > 0)){
                    return;
                }
                break;
            case ')':
                if(!dont){
                    result_part_2 += rhs * lhs;
                }
                result_part_1 += rhs*lhs;
                break;
        }
    }
    ungetc(c,file);
}


int solve(){
    char c = '0';
    FILE* file = fopen(INPUT_FILE,"r");
    while ((c = fgetc(file)) != EOF){
        switch(c){
            case 'm':
            check_mul(file);
            case 'd':
                (dont) ? check_do(file) : check_dont(file);
        }
    }
    fclose(file);
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