int compute() {
    int local_val = 42;
    return local_val;
}

int main() {
    int access_error = 0;
    access_error = local_val + 10; // Error: local_val is trapped inside compute()
    return 0;
}