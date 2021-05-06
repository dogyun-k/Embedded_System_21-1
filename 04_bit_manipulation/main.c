//reference
// #define P0HW_ADDR 0x40000000
// #define P0HW *(unsigned char*)P0HW_ADDR
int sum(int x, int y){
    return x + y;
}   
int main(){
    
    int x;
    int y;
    int z;

    x = 3;
    y = 5;
    z = x + y;
    z = x - y;

    z = sum(x, y);
}
