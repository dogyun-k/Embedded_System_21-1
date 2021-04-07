//reference
// #define P0HW_ADDR 0x40000000
// #define P0HW *(unsigned char*)P0HW_ADDR

int main(){
    
    int x;
    int y;
    int z;

    x = 3;
    y = 5;
    z = x + y;
    z = x - y;

    if(x > 3){
        x += 2;
    }
    else{
        x -= 2;
    }

    for(int i = 0; i < 5; i++){
        y += 1;
    }

    z = sum(x, y);
}
