import "math.c";

int add(int a, int b){
    return a+b;
}

int main(){
    int x = 10;
    int y = 20;
    int z = x + y;

    if(z > 10){
        z = z + 1;
    }

    return z;
}