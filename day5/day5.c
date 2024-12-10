#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#define LINE_SIZE (500)
#define DIR_SIZE (100)

static LinkedList_t** list;
static int number;
static int value;
static int key;
static char c;

int get_number(FILE* file, char nbr){
    int number = (nbr-'0');
    while((c = fgetc(file)) != EOF && isdigit(c)){
            number = number * 10 + (c - '0');
    }
    return number;
}

void skip_to_newline(FILE *file){
    char buffer [LINE_SIZE];
    fgets(buffer, LINE_SIZE, file);
}

int solve(){
    FILE* file = fopen(INPUT_FILE,"r");
    list = create_linked_list();

    while ((c = fgetc(file)) != EOF){
        if(isdigit(c)){
            number = get_number(file,c);
        }
        switch(c){
            case '|':
                key = number;
                value = get_number(file ,c);
                create_and_append(list[key], value);
                skip_to_newline(file);
                break;
            case ',':
            case '\n':
                break;
        }
    }
    fclose(file);
    return 0;
}


int main(){
    read_data(5);
    solve();
}