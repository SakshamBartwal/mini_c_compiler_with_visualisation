#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler/3_ast/ast.h"
#include "compiler/4_semantics/semantic.h"
#include "compiler/4_semantics/symbol_table.h" 
#include "compiler/5_tac/tac.h" 
#include "compiler/6_cfg/cfg.h"

// Global tracking anchors required by the parser link
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


    // Initialize target file logging properties
    strncpy(current_file, argv[1], sizeof(current_file) - 1);
    printf("Compiling file: %s\n", current_file);


    // Open the entry file stream context for Flex
    extern FILE *yyin;
    yyin = fopen(current_file, "r");

    if (!yyin) {
        fprintf(stderr, "System Error: Cannot open source file '%s'\n", current_file);
        return 1;
    }


    // Run parsing execution passes via Bison
    extern int yyparse();

    if (yyparse() != 0) {
        printf("\nParsing Failed due to syntax errors.\n");
        fclose(yyin);
        return 1;
    }


    printf("\n=====================================\n");
    printf(" Parsing Successful\n");
    printf(" No syntax errors found\n");
    printf("=====================================\n");


    // Print out the raw global Abstract Syntax Tree structural blueprint to the console
    printf("\n=========== AST ===========\n");
    print_ast(root, 0);


    // Run middle-end semantic scope boundary checking passes
    analyze_semantics(root);


    // Generate flat Three-Address Code instructions from the AST root entry
    generate_tac(root);


    // Print the intermediate representation code blocks out line-by-line
    print_tac();


    // Partition the linear instruction stream into basic blocks and trace routes
    build_cfg();
    print_cfg();


    // Close the file stream cleanly before packaging the data outputs
    fclose(yyin);


    /* ============================================================================
       UI Visualizer Layer JSON Serialization Exports
       ============================================================================ */

    // 1. Export full Abstract Syntax Tree structure mappings
    export_ast_to_json(root, "ast.json");

    // 2. Export interactive Control Flow Graph basic blocks and jump nodes
    export_cfg_to_json("cfg.json");

    // 3. Export global and localized structural Symbol Table snapshots
    export_symbols_to_json("symbols.json");


    return 0;
}