//reference
// #define P0HW_ADDR 0x40000000
// #define P0HW *(unsigned char*)P0HW_ADDR

int main(){
    
    char P0;

    P0 = 0x95; // 1001 0101
    P0 &= ~(0x10);

	while(1);
}
