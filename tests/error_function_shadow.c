int process_data(int scope_id, int factor) {
    int alpha = 10;
    int scope_id = 50; /* SEMANTIC ERROR: 'scope_id' redefinition overrides incoming parameter! */

    return alpha * factor;
}

int main() {
    int result = 0;
    result = process_data(1, 5);
    return 0;
} 