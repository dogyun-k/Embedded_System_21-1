#include <stdio.h>
#include <stdint.h>


int main(void){

    int32_t var;
    
    var = 0xfe4;

    // var |= 0xfffff000;
    var <<= 20;
    // var >>= 20;

    printf("%x | %d\n", var, var);

    return 0;
}