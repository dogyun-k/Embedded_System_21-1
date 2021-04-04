//reference
// #define P0HW_ADDR 0x40000000
// #define P0HW *(unsigned char*)P0HW_ADDR
int sum(int a, int b){
    return a+b;
}

int main(){
    
    char P0;
    int x;
    int y;

    x = 3;
    y = 5;

    P0 = 0x95; // 1001 0101
    P0 &= ~(0x10);

    //P0HWr = 0x4f;

    sum(x, y);

	while(1);
}
