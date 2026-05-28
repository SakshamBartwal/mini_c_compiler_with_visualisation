#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "3_ast/ast.h"

extern FILE *yyin;
extern int yyparse();

extern int line_num;



char current_file[100];

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *source_file = fopen(argv[1], "r");

    if(source_file == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    strcpy(current_file, argv[1]);

    yyin = source_file;

    printf("=====================================\n");
    printf(" Mini-C Compiler\n");
    printf("=====================================\n");

    printf("Compiling file: %s\n\n", current_file);

    int result = yyparse();

    if(result == 0) {

        printf("\n=====================================\n");
        printf(" Parsing Successful\n");
        printf(" No syntax errors found\n");
        printf("=====================================\n");

        if(root != NULL)
        {
            printf("\n=========== AST ===========\n\n");

            print_ast(root, 0);
        }
    }
    else {

        printf("\n=====================================\n");
        printf(" Parsing Failed\n");
        printf("=====================================\n");
    }

    fclose(source_file);

    return 0;
}