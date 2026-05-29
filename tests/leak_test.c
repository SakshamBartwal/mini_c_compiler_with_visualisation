import "tests/math_core.c";

int main() {
    int total = 10;
    
    /* SEMANTIC ERROR: 'triple' exists strictly inside 'triple_value' framework! */
    /* Your semantic analyzer must catch this variable breach and halt compilation! */
    total = total + triple; 
    
    return 0;
}