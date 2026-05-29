import "tests/math_core.c";

int process_increment(int input_val) {
    int stepped = input_val + 1;
    int tripled = triple_value(stepped);
    return tripled;
}