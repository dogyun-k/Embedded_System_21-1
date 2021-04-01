#include <stdio.h>

int main(void){

    unsigned int led  = 0;
    unsigned int cnt = 0;

    while(1){
        if(cnt % 2 == 0){
            led = 1;
        }
        else{
            led = 0;
        }
        cnt++;
    }


    return 0;
}
