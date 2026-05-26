import "math.c";

/* ---------------- GLOBALS ---------------- */

int globalA = 10;

int duplicateGlobal = 1;
int duplicateGlobal = 2;     // ERROR

int sameName = 100;

int conflict;
int conflict(){              // ERROR
    return 0;
}

/* ---------------- FUNCTION 1 ---------------- */

int alpha(int p1, int p2){

    int localX = 10;

    int localX = 20;         // ERROR

    globalA = 500;           // VALID

    p1 = p1 + p2;            // VALID

    undeclaredA = 5;         // ERROR

    int shadow = 1;

    {
        int shadow = 2;      // currently may ERROR
    }

    return localX;
}

/* ---------------- DUPLICATE FUNCTION ---------------- */

int alpha(int x){            // ERROR

    return x;
}

/* ---------------- FUNCTION 2 ---------------- */

int beta(){

    int localX = 50;         // VALID

    globalA = 200;           // VALID

    int sameName = 999;      // VALID shadowing

    return localX;
}

/* ---------------- PARAMETER TEST ---------------- */

int gamma(int x){

    int y = x;               // VALID

    int x = 100;             // ERROR

    y = undeclaredY;         // ERROR

    return y;
}

/* ---------------- FUNCTION ISOLATION ---------------- */

int delta(){

    int isolated = 1;

    return isolated;
}

int epsilon(){

    int isolated = 2;        // VALID

    return isolated;
}

/* ---------------- GLOBAL LOOKUP TEST ---------------- */

int globalCounter = 0;

int increment(){

    globalCounter = globalCounter + 1;

    return globalCounter;
}

/* ---------------- FUNCTION CALL STYLE EXPRESSIONS ---------------- */

int compute(int a, int b){

    int result = a + b;

    result = result + globalA;

    return result;
}

/* ---------------- MAIN ---------------- */

int main(){

    int x = 10;

    int y = x + globalA;

    y = undeclaredMain;      // ERROR

    int x = 20;              // ERROR

    return y;
}