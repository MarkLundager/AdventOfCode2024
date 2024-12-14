#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>
#define DAY (6)



typedef enum ENTITY{
    OBSTACLE,
    CLEAR,
    OCCUPIED
}ENTITY;

typedef struct Prev_Pos_t{
    short x;
    short y;
    short dx;
    short dy;
    struct Prev_Pos_t* next;
} Prev_Pos_t;

typedef struct Guard_t{
    short x;
    short y;
    signed short dx :2;
    signed short dy :2;
    struct Guard_t* next;
} Guard_t;

ENTITY ** layout;
Guard_t * guards;
static int result, result2;
static short ncols, row, col;
char c;

void append_prev_pos(int x,int y, Prev_Pos_t** head,int dx, int dy){
    Prev_Pos_t* new_pos = malloc(sizeof(*new_pos));
    new_pos->x = x;
    new_pos->y = y;
    new_pos->dx = dx;
    new_pos->dy = dy;
    new_pos->next = NULL;
    if(*head == NULL){
        *head = new_pos;
        return;
    }
    Prev_Pos_t* current = *head;
    while(current->next != NULL){

        current = current->next;
    }
    current->next = new_pos;
}

void freepos(Prev_Pos_t *p){
    Prev_Pos_t * temp;
    while(p != NULL){
        temp = p;
        p=p->next;
        free(temp);
    }
}

void free_guard(Guard_t *p){
    Guard_t * temp;
    while(p != NULL){
        temp = p;
        p=p->next;
        free(temp);
    }
}

void append_node(ENTITY entity){
    layout[row][col] = entity;

    if(entity == OCCUPIED){
        result ++;
        Guard_t* new_guard = malloc(sizeof(*new_guard));
        new_guard->x = row;
        new_guard->y = col;
        new_guard->dx = -1;
        new_guard->dy = 0;
        new_guard->next = NULL;
        if (guards == NULL){
            guards = new_guard;
            return;
        }
        while(guards->next != NULL){
            guards = guards->next;
        }
        guards->next = new_guard;
    }
}

void handle_char(char c){
    switch(c){
        case '#':
            append_node(OBSTACLE);
            break;
        case '.':
            append_node(CLEAR);
            break;
        case '^':
            append_node(OCCUPIED);
            break;
    }
}

void count_cols(FILE* file){
    while ((c = fgetc(file)) != '\n' && c != EOF){
        if(!isspace(c)) ncols ++;
    }
    rewind(file);
}

void read_data_into_memory(int day){
    read_data(day);
    FILE* file = fopen(INPUT_FILE,"r");
    count_cols(file);
    layout = malloc(ncols * sizeof(*layout));
    layout[0] = malloc(ncols * sizeof(*layout[0]));
    if(layout == NULL){
        perror("not enough space");
        return;
    }
    while ((c = fgetc(file)) != EOF){
        switch(c){
            case '\n':
                row ++;
                layout[row] = malloc(sizeof(*layout[row]) * ncols);
                if(layout[row] == NULL){
                    perror("not enough space");
                return;
                }
                col = 0;
                break;
            default:
                handle_char(c);
                col ++;
                break;
        }
    }
    fclose(file);
    return;
}

static void rotate_90_cw(int* dx, int *dy ){
    int temp = *dy;
    *dy = -(*dx);
    *dx = temp;
}
bool check_bounds(int x, int y){
    return (x<ncols && x >= 0 && y < ncols && y>=0);
}
void simulate_guard(int x, int y, int dx, int dy, bool obstruction_set, Prev_Pos_t* prev_pos, int obstr_x, int obstr_y){
    while(true){
        if(!check_bounds(x+dx,y+dy)){
            freepos(prev_pos);
            return;
        }
        switch(layout[x+dx][y+dy]){
            case CLEAR:
                if(!obstruction_set){
                    result ++;
                    layout[x+dx][y+dy] = OCCUPIED;
                    Prev_Pos_t* new_pos = NULL; 
                    append_prev_pos(x,y,&new_pos,dx,dy);
                    int i = dx;
                    int j = dy;
                    rotate_90_cw(&i,&j);
                    simulate_guard(x,y,i,j,true, new_pos, x+dx,y+dy);
                }
            case OCCUPIED:
                if(obstruction_set && x+dx == obstr_x && y+dy == obstr_y){
                    append_prev_pos(x,y,&prev_pos, dx, dy);
                    rotate_90_cw(&dx,&dy);
                    break;
                }
                x += dx;
                y += dy;
                break;
            case OBSTACLE:
                if(obstruction_set){
                    Prev_Pos_t* head = prev_pos;
                    while(head != NULL){
                        if(head->x == x && head->y == y && head->dx == dx && head->dy == dy){
                            result2++;
                            freepos(prev_pos);
                            return;
                        }
                    head = head->next;
                    }
                    append_prev_pos(x,y,&prev_pos, dx, dy);
                }
                rotate_90_cw(&dx,&dy);
                break;
        }
    }
}

int solve(){
    Guard_t* guard = guards;
    while(guard != NULL){
        simulate_guard(guard->x, guard->y, guard->dx, guard->dy,false,NULL,0,0);
        guard = guard->next;
    }
    free_guard(guards);
    printf("Part 1 result: %d\n", result);
    printf("Part 2 result: %d\n", result2);
    return 0;
}


int main(){
    read_data_into_memory(DAY);
    solve();

}