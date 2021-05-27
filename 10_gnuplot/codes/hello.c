#include <stdio.h>

int main(void){

    int y;
    FILE* file_out;

    file_out = fopen("out.txt", "w");

    for(int i = 0; i < 100; i++){
        y = 5 * i + 10;
        fprintf(file_out, "%d \t %d \n", i, y);
    }

    return 0;
}   
