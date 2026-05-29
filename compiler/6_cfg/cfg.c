#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfg.h"

BasicBlock *cfg_head = NULL;
int block_id_counter = 0;

/* Helper utility to allocate a fresh execution basic block */
BasicBlock* create_basic_block(TACInstr *start) {
    BasicBlock *bb = malloc(sizeof(BasicBlock));
    bb->id = block_id_counter++;
    sprintf(bb->name, "Block_%d", bb->id);
    bb->start_instr = start;
    bb->end_instr = start;
    bb->true_exit = NULL;
    bb->false_exit = NULL;
    bb->next = NULL;
    return bb;
}

/* Core CFG Partitioning Engine */
void build_cfg() {
    if (tac_head == NULL) return;

    /* Reset global variables in case of multiple runs */
    cfg_head = NULL;
    block_id_counter = 0;

    BasicBlock *cfg_tail_list = NULL;
    TACInstr *curr_instr = tac_head;
    
    /* State flag: Forces a fresh block to start whenever an execution boundary is crossed */
    int force_new_block = 1; 

    /* PASS 1: Identify leaders and slice the linear TAC list into basic blocks safely */
    while (curr_instr != NULL) {
        
        /* A line starts a block if it is an entry point, an explicit label, or follows a branch */
        if (curr_instr->op == TAC_FUNC_START || 
            curr_instr->op == TAC_LABEL || 
            force_new_block) {
            
            BasicBlock *new_bb = create_basic_block(curr_instr);
            
            if (cfg_head == NULL) {
                cfg_head = new_bb;
                cfg_tail_list = new_bb;
            } else {
                cfg_tail_list->next = new_bb;
                cfg_tail_list = new_bb;
            }
            
            force_new_block = 0;
        } else {
            /* Keep expanding the current active basic block boundary */
            if (cfg_tail_list != NULL) {
                cfg_tail_list->end_instr = curr_instr;
            }
        }

        /* If this instruction branches or returns, the NEXT instruction MUST start a block */
        if (curr_instr->op == TAC_GOTO || 
            curr_instr->op == TAC_IF_FALSE || 
            curr_instr->op == TAC_RETURN) {
            force_new_block = 1;
        }

        curr_instr = curr_instr->next;
    }

    /* PASS 2: Trace and map branching exit edges across the blocks */
    BasicBlock *b = cfg_head;
    while (b != NULL) {
        TACInstr *last = b->end_instr;
        if (last == NULL) {
            b = b->next;
            continue;
        }

        if (last->op == TAC_GOTO) {
            /* Unconditional jump: Find the target block starting with this label destination string */
            BasicBlock *target = cfg_head;
            while (target != NULL) {
                if (target->start_instr->op == TAC_LABEL && 
                    strcmp(target->start_instr->dest, last->dest) == 0) {
                    b->true_exit = target;
                    break;
                }
                target = target->next;
            }
        } 
        else if (last->op == TAC_IF_FALSE) {
            /* Conditional split: true_exit handles code fall-through, false_exit handles jump path */
            b->true_exit = b->next; 

            BasicBlock *target = cfg_head;
            while (target != NULL) {
                if (target->start_instr->op == TAC_LABEL && 
                    strcmp(target->start_instr->dest, last->dest) == 0) {
                    b->false_exit = target;
                    break;
                }
                target = target->next;
            }
        } 
        else if (last->op != TAC_RETURN) {
            /* Standard continuous code blocks fall straight forward into the neighbor block entry */
            b->true_exit = b->next;
        }

        b = b->next;
    }
}

/* Visualization utility prints out basic blocks layout to terminal dashboard */
void print_cfg() {
    printf("\n=========== Control Flow Graph (CFG) ===========\n");
    BasicBlock *b = cfg_head;
    while (b != NULL) {
        printf("%s:\n", b->name);
        
        TACInstr *i = b->start_instr;
        while (1) {
            if (i->op == TAC_FUNC_START) printf("    func %s:\n", i->dest);
            else if (i->op == TAC_LABEL) printf("    %s:\n", i->dest);
            else if (i->op == TAC_ASSIGN) printf("        %s = %s\n", i->dest, i->arg1);
            else if (i->op == TAC_ADD) printf("        %s = %s + %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_SUB) printf("        %s = %s - %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_MUL) printf("        %s = %s * %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_DIV) printf("        %s = %s / %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_LT)  printf("        %s = %s < %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_GT)  printf("        %s = %s > %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_EQ)  printf("        %s = %s == %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_NEQ) printf("        %s = %s != %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_LE)  printf("        %s = %s <= %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_GE)  printf("        %s = %s >= %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_IF_FALSE) printf("        if_false %s goto %s\n", i->arg1, i->dest);
            else if (i->op == TAC_GOTO) printf("        goto %s\n", i->dest);
            else if (i->op == TAC_RETURN) printf("        return %s\n", i->dest ? i->dest : "");

            if (i == b->end_instr) break;
            i = i->next;
        }

        /* Print edge relationships linking blocks */
        if (b->true_exit)  printf("  --> [True / Fallthrough Path] links to %s\n", b->true_exit->name);
        if (b->false_exit) printf("  --> [False / Branch Jump Path] links to %s\n", b->false_exit->name);
        printf("\n");

        b = b->next;
    }
}