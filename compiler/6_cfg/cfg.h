#ifndef CFG_H
#define CFG_H

#include "compiler/3_ast/ast.h"
#include "compiler/5_tac/tac.h"



// The structure representing an isolated Basic Block chunk in our execution graph
typedef struct BasicBlock {

    int id;                        // Unique ID number used by React Flow to draw this block
    char name[20];                 // Friendly descriptor name (like Block_0, Block_1)
    
    TACInstr *start_instr;         // Points to the very first intermediate line inside this block
    TACInstr *end_instr;           // Points to the absolute final instruction inside this block
    
    struct BasicBlock *true_exit;  // Where we go next on a true branch outcome or normal fall-through
    struct BasicBlock *false_exit; // Where we skip to if a conditional branch test fails (if_false)
    
    struct BasicBlock *next;       // Sequential link list pointer to track all allocated blocks in memory

} BasicBlock;



// Global anchor tracking the starting head location of your control flow blocks
extern BasicBlock *cfg_head;



/* ============================================================================
   Engine Interface Modules
   ============================================================================ */

// Identifies execution leaders, cuts instructions into blocks, and maps branches
void build_cfg();


// Debug tool to print out a visual outline of blocks and connections into terminal logs
void print_cfg();


// Walks your live block linked list and maps the geometry into a JSON file for the UI
void export_cfg_to_json(const char *filename);



#endif