int fib(int n);

int fib(int n) {

    if(n <= 1) {
        return n;
    }

    return fib(n - 1) + fib(n - 2);
}

int main() {

    int result = 0;

    int arr[10][20];

    for(int i = 0; i < 10; i++) {

        for(int j = 0; j < 20; j++) {

            arr[i][j] = i * j;
        }
    }

    result = fib(5);

    result = (result > 5) ? result : 5;

    return result;
}