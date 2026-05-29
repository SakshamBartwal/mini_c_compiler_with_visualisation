#ifndef CFG_H
#define CFG_H

#include "compiler/3_ast/ast.h"
#include "compiler/5_tac/tac.h"

/* Structure representing a unified Basic Block chunk */
typedef struct BasicBlock {
    int id;                        /* Unique identifier for block node rendering */
    char name[20];                 /* Descriptor name (e.g., Block_0, Block_1) */
    TACInstr *start_instr;         /* Points to the first TAC instruction in the block */
    TACInstr *end_instr;           /* Points to the last TAC instruction in the block */
    
    struct BasicBlock *true_exit;  /* Target block for True conditions or sequential fallthrough */
    struct BasicBlock *false_exit; /* Target block if a conditional jump (if_false) triggers */
    struct BasicBlock *next;       /* Linear tracking link to list all allocated blocks */
} BasicBlock;

/* Global anchor tracking the head of your program graph blocks */
extern BasicBlock *cfg_head;

/* Engine interface modules */
void build_cfg();
void print_cfg();

#endif