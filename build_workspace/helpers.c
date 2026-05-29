// Module file: helpers.c
// Global state tracking variable
int global_counter = 100;

// Utility function to compute step configurations
int calculate_step(int current_val) {
    int step_multiplier = 2;
    int result = current_val * step_multiplier;
    
    return result;
}