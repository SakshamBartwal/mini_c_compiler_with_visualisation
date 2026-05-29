#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "compiler/3_ast/ast.h"
#include "symbol_table.h" 



/* ============================================================================
   Engine Interface Modules
   ============================================================================ */

// The main entry point used by main.c to start processing the semantic analysis phase
void analyze_semantics(ASTNode *root);


// The internal recursive worker that travels down the AST branches to verify variable scopes
void semantic_walk(ASTNode *node, SymbolTable *current_scope);



#endif