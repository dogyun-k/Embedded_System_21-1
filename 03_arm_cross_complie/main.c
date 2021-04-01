 #include <stdio.h>

int main(void){

    unsigned int led  = 0;
    int count = 0;

    while(1){
        if(count % 2 == 0){
            led = 1;
        }
        else{
            led = 0;
        }
        printf("led = %d\n", led);
        count++;
    }


    return 0;
}
