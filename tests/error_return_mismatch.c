int compute_delta() {
    int delta_modifier = 45;
    return delta_modifier;
}

int main() {
    int total = 100;
    /* SEMANTIC ERROR: 'delta_modifier' belongs strictly to compute_delta's scope stack! */
    total = total + delta_modifier; 
    
    return 0;
}