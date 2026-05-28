int main() {
    int a = 1;
    int b = 2;

    for (int i = 0; i < 10; i = i + 1) {
        if (a < b) {
            int temp = a;
            a = b;
            b = temp;
        } else {
            while (a > 0) {
                a = a - 1;
                if (a == 5) {
                    break;
                }
            }
        }
    }
    return 0;
}