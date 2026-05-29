#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler/3_ast/ast.h"
#include "compiler/4_semantics/semantic.h"
#include "compiler/5_tac/tac.h" /* 1. INCLUDE THE TAC LAYER HEADER */
#include "compiler/6_cfg/cfg.h"

/* Global tracking anchors required by the parser link */
extern ASTNode *root;
char current_file[100];

int main(int argc, char *argv[]) {
    printf("=====================================\n");
    printf(" Mini-C Compiler\n");
    printf("=====================================\n");

    if (argc < 2) {
        fprintf(stderr, "Usage Error: Missing target file path argument.\n");
        return 1;
    }

    /* Initialize target file logging properties */
    strncpy(current_file, argv[1], sizeof(current_file) - 1);
    printf("Compiling file: %s\n", current_file);

    /* Open the entry file stream context for Flex */
    extern FILE *yyin;
    yyin = fopen(current_file, "r");
    if (!yyin) {
        fprintf(stderr, "System Error: Cannot open source file '%s'\n", current_file);
        return 1;
    }

    /* Run parsing execution passes */
    extern int yyparse();
    if (yyparse() != 0) {
        printf("\nParsing Failed due to syntax errors.\n");
        return 1;
    }

    printf("\n=====================================\n");
    printf(" Parsing Successful\n");
    printf(" No syntax errors found\n");
    printf("=====================================\n");

    /* Print out the raw global Abstract Syntax Tree structural blueprint */
    printf("\n=========== AST ===========\n");
    print_ast(root, 0);

    /* Run middle-end semantic scope boundary checking passes */
    analyze_semantics(root);

    /* 2. GENERATE FLAT THREE-ADDRESS CODE FROM THE AST ROOT ENTRY */
    generate_tac(root);

    /* 3. PRINT THE CODE BLOCKS OUT LINE-BY-LINE */
    print_tac();

    build_cfg();
    print_cfg();

    fclose(yyin);
    return 0;
}