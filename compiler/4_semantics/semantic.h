#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "compiler/3_ast/ast.h"
#include "symbol_table.h" /* Updated include */

/* Entry point to analyze the complete Abstract Syntax Tree */
void analyze_semantics(ASTNode *root);

/* Internal recursive tree walker */
void semantic_walk(ASTNode *node, SymbolTable *current_scope);

#endif