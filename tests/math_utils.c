int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i = i + 1) {
        res = res * base;
    }
    return res;
}

int calculate_square(int num) {
    int answer = 0;
    answer = power(num, 2);
    return answer;
}