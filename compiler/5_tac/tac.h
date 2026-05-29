#ifndef TAC_H
#define TAC_H

#include "compiler/3_ast/ast.h"

typedef enum {
    TAC_ASSIGN,     
    TAC_ADD,        
    TAC_SUB,        
    TAC_MUL,        
    TAC_DIV,        
    TAC_RETURN,     
    TAC_FUNC_START,
    /* === NEW CONTROL FLOW OPERATIONS === */
    TAC_LABEL,       /* Marks a jump location target (e.g., L0:) */
    TAC_IF_FALSE,    /* Conditional jump: if_false arg1 goto dest */
    TAC_GOTO,         /* Unconditional jump: goto dest */
    /* === ADD THESE RELATIONAL OPERATIONS === */
    TAC_LT,          /* <  */
    TAC_GT,          /* >  */
    TAC_EQ,          /* == */
    TAC_NEQ,         /* != */
    TAC_LE,          /* <= */
    TAC_GE           /* >= */
} TACOp;

typedef struct TACInstr {
    TACOp op;               
    char *dest;             
    char *arg1;             
    char *arg2;             
    struct TACInstr *next;  
} TACInstr;

extern TACInstr *tac_head;
extern TACInstr *tac_tail;

char* new_temp();
char* new_label(); /* <-- ADD THIS PROTOTYPE */
void emit(TACOp op, const char *dest, const char *arg1, const char *arg2);
char* generate_tac(ASTNode *root);
void print_tac();

#endif