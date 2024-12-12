#include <stdio.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include<unistd.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>


static int result;
static int result2;




int solve(){
    FILE* file = fopen(INPUT_FILE,"r");




    fclose(file);
    printf("Part 1 result: %d\n", result);
    printf("Part 2 result: %d\n", result2);
    return 0;
}


int main(){
    //read_data(6);
    solve();


}