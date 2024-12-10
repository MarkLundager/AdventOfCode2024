#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#define BUFFER_SIZE (500)
#define DIR_SIZE (100)
#define middle(x) ((x) / 2)
static LinkedList_t** list;
static int number;
static int key;
static char c;
static int result;
static int result2;

int get_number(FILE* file, char nbr){
    int number = (nbr-'0');
    while((c = fgetc(file)) != EOF && isdigit(c) && c != '\n'){
            number = number * 10 + (c - '0');
    }
    return number;
}

int extract_middle_value(int i, LinkedList_t * l_list){
    LinkedList_t * temp = l_list;
    for(int j = 0; j<i; j++){
        temp = temp->next;
    }
    return temp->value;
}

void skip_line(FILE *file){
    char buffer [BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, file);
}

void sort_update(LinkedList_t * l_list){

}

void checkrow(LinkedList_t * l_list){
    bool correct = true;
    int i = 0;
    int head_value;
    LinkedList_t * head = l_list;
    while(head != NULL && correct){
        LinkedList_t * tail = head->next;
        head_value = head->value;
        while(tail != NULL && correct){
            LinkedList_t* rules = list[tail->value];
            while(rules != NULL && correct){
                if(head_value == rules->value){
                    correct = false;
                }
                rules = rules->next;
            }
            tail = tail->next;
        }
        head = head->next;
        i++;
    }
    if(correct){
        result += extract_middle_value(middle(i), l_list);
    }
    else{
        sort_update(l_list);
        result2 += extract_middle_value(middle(i), l_list);
    }

}

void process_line(FILE* file){

    LinkedList_t * head = NULL;
    create_and_append(&head, number);
    char buffer [BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, file);
    char *token = strtok(buffer, ",");

    while(token != NULL){
        sscanf(token, "%d", &number);
        create_and_append(&head, number);
        token = strtok(NULL, ",");
    }
    checkrow(head);
    free(head);
}

int solve(){
    FILE* file = fopen(INPUT_FILE,"r");
    while ((c = fgetc(file)) != EOF){
        if(isdigit(c)){
            number = get_number(file,c);
        }

        switch(c){
            case '|':
                key = number;
                number = get_number(file ,'0');
                create_and_append(&list[key], number);
                skip_line(file);
                break;
            case ',':
                key = number;
                process_line(file);
        }
    }
    fclose(file);
    printf("Part 1 result: %d\n", result);
    return 0;
}


int main(){
    read_data(5);

    list = malloc(sizeof(*list) * DIR_SIZE);
    for(int i = 0; i<DIR_SIZE; i++){
        list[i] = NULL;
    }
    solve();
    for(int i = 0; i<DIR_SIZE; i++){
        free_linked_list(&list[i]);
    }
    free(list);

}