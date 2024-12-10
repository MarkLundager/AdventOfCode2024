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


void checkrow(LinkedList_t * l_list, int length){
            bool correct = true;
            int head_value;
            LinkedList_t * head = l_list;
restart:    while(head != NULL){
                LinkedList_t * tail = head->next;
                head_value = head->value;
                while(tail != NULL){
                    LinkedList_t* rules = list[tail->value];
                    while(rules != NULL){
                        if(head_value == rules->value){
                            correct = false;
                            swap(&head, &tail);
                            head = l_list;
                            goto restart;
                        }
                        rules = rules->next;
                    }
                    tail = tail->next;
                }
                head = head->next;
            }
            if(correct){
                result += extract_middle_value(middle(length), l_list);
            }
            else{
                result2 += extract_middle_value(middle(length), l_list);
            }
    }

void process_line(FILE* file){
    int i = 1;
    LinkedList_t * head = NULL;
    create_and_append(&head, number);
    char buffer [BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, file);
    char *token = strtok(buffer, ",");

    while(token != NULL){
        sscanf(token, "%d", &number);
        create_and_append(&head, number);
        token = strtok(NULL, ",");
        i++;
    }
    checkrow(head, i);
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
                break;
            case ',':
                key = number;
                process_line(file);
        }
    }
    fclose(file);
    printf("Part 1 result: %d\n", result);
    printf("Part 2 result: %d\n", result2);
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