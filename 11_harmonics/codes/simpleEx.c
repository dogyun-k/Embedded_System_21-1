#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define F 400   // sampling speed
#define T 1/F
#define A 5.0
#define PI 3.14

int main(void){
    FILE* file_out;
    file_out = fopen("out.txt", "w");

    int hi = 2; // harmonics 1 Hz

    for(int i = 0; i <= 400; i++) {     // i : 
        float signal = (float)A * sin(2*PI*hi*T*i);     // adc value 
        fprintf(file_out, "%d \t %.2f \n", i, signal);
    }

    return 0;
}   
