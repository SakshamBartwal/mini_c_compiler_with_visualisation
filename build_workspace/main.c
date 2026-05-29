import "helpers.c";

int main() {
    int i = 0;
    int sum = 0;
    
    // Local variable shadowing the global identifier name cleanly
    int global_counter = 5;

    while (i < global_counter) {
        int loop_increment = calculate_step(i);
        sum = sum + loop_increment;
        i = i + 1;
    }

    return 0;
}