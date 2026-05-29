#ifndef TAC_H
#define TAC_H

#include "compiler/3_ast/ast.h"



// Operational codes representing every flat Three-Address Code instruction type
typedef enum {

    TAC_ASSIGN,     
    TAC_ADD,        
    TAC_SUB,        
    TAC_MUL,        
    TAC_DIV,        
    TAC_RETURN,     
    TAC_FUNC_START,

    // Branching and jump targets for structural loops and conditionals
    TAC_LABEL,       
    TAC_IF_FALSE,    
    TAC_GOTO,         

    // Relational comparison checkers
    TAC_LT,          
    TAC_GT,          
    TAC_EQ,          
    TAC_NEQ,         
    TAC_LE,          
    TAC_GE           

} TACOp;



// The structure for a single Three-Address Code instruction quadruple line
typedef struct TACInstr {

    TACOp op;               // The operation identifier opcode mapping
    char *dest;             // The destination location variable or temporary register string
    char *arg1;             // The primary input operator argument string
    char *arg2;             // The secondary input operator argument string
    
    struct TACInstr *next;  // Linear track pointer to find the subsequent chronological step

} TACInstr;



// Head and tail anchors to track our flat intermediate instruction listing across memory
extern TACInstr *tac_head;
extern TACInstr *tac_tail;



/* ============================================================================
   Register and Target Reference Generators
   ============================================================================ */

// Provisions a fresh unique temporary computing variable name (e.g. t0, t1)
char* new_temp();


// Provisions a fresh unique branching anchor location name (e.g. L0, L1)
char* new_label(); 



/* ============================================================================
   Engine Interface Modules
   ============================================================================ */

// Formats a new operational node context and flattens it directly onto our tail listing
void emit(TACOp op, const char *dest, const char *arg1, const char *arg2);


// Recursively traverses structural abstract syntax tree nodes to build out flat lines
char* generate_tac(ASTNode *root);


// Debug tool to print out every instruction step linearly onto the terminal window
void print_tac();



#endif