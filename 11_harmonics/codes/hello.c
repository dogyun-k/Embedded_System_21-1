#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define F 200   // sampling speed
#define T 1/F   // sampling period
#define A 5.0   // amplitude
#define N 200   // number of sampele depth

#define PI 3.14

int main(void){
    FILE* file_out;
    file_out = fopen("out.txt", "w");

    float polynomial[N];

    // signal getneration (sum of harmonics)
    for(int i = 0; i <= N; i++) {     // time advance
        
        int hi = 1; // harmonics 1 Hz
        polynomial[i] = 0;
        
        for(int j = 0; j < 32; j++){    // frequency advance
            float signal = (float) (A / hi) * sin(2 * PI * hi * T * i);     // adc value 
            polynomial[i] += signal;
            hi += 2;
        }

        // plot
        // fprintf(file_out, "%d \t %.2f \n", i, polynomial[i]);
    }


    
    // fourier analysis
    // int probe_freq = 2;

    for(int probe_freq = 0; probe_freq < 32; probe_freq++){

        float freq_component = 0;
        for(int i = 0; i < N; i++){
            float probe = (float) (A) * sin(2 * PI * probe_freq * T * i);

            freq_component += polynomial[i] * probe;
        }

        printf("%d Hz component strength is %.1f\n", probe_freq, freq_component);
        fprintf(file_out, "%d \t %f \n", probe_freq, freq_component);
    } 


    
    
    
    return 0;
}   
