#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfg.h"

BasicBlock *cfg_head = NULL;
int block_id_counter = 0;



// Helper utility to allocate a fresh, isolated execution basic block chunk
BasicBlock* create_basic_block(TACInstr *start) {

    BasicBlock *bb = malloc(sizeof(BasicBlock));

    bb->id = block_id_counter++;
    sprintf(bb->name, "Block_%d", bb->id);
    
    // Default boundaries clamp onto the starting instruction initially
    bb->start_instr = start;
    bb->end_instr   = start;
    
    bb->true_exit   = NULL;
    bb->false_exit  = NULL;
    bb->next        = NULL;

    return bb;
}



// Core CFG Partitioning Engine: Slices up linear instructions and connects execution pathways
void build_cfg() {

    if (tac_head == NULL) {
        return;
    }

    // Reset tracking counters and state variables for subsequent clean compilation passes
    cfg_head = NULL;
    block_id_counter = 0;

    BasicBlock *cfg_tail_list = NULL;
    TACInstr *curr_instr = tac_head;
    
    // Trigger flag forcing a new basic block chunk to spawn when boundaries are crossed
    int force_new_block = 1; 


    // ------------------------------------------------------------------------
    // PASS 1: Identify execution leaders and slice up your flat linear TAC list
    // ------------------------------------------------------------------------
    while (curr_instr != NULL) {
        
        // A fresh block starts if we see a function entry, an explicit label target, or a post-jump line
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
            // Otherwise, stretch out the active block boundary to engulf this instruction
            if (cfg_tail_list != NULL) {
                cfg_tail_list->end_instr = curr_instr;
            }
        }

        // If this line explicitly redirects code execution, the next instruction MUST be a fresh leader
        if (curr_instr->op == TAC_GOTO || 
            curr_instr->op == TAC_IF_FALSE || 
            curr_instr->op == TAC_RETURN) {
            
            force_new_block = 1;
        }

        curr_instr = curr_instr->next;
    }


    // ------------------------------------------------------------------------
    // PASS 2: Trace trailing instructions and link edge pointers across blocks
    // ------------------------------------------------------------------------
    BasicBlock *b = cfg_head;

    while (b != NULL) {
        TACInstr *last = b->end_instr;

        if (last == NULL) {
            b = b->next;
            continue;
        }


        if (last->op == TAC_GOTO) {
            // Unconditional jumps point straight to their matching label block targets
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
            // Conditional branches split two ways: true fall-through vs false label skip path
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
            // Standard continuous lines fall forward straight into the entry of the next block
            b->true_exit = b->next;
        }

        b = b->next;
    }
}



// Formats and prints out your segmented blocks and execution routes onto the dashboard terminal
void print_cfg() {

    printf("\n=========== Control Flow Graph (CFG) ===========\n");
    BasicBlock *b = cfg_head;


    while (b != NULL) {
        printf("%s:\n", b->name);
        TACInstr *i = b->start_instr;

        // Print inner instructions packaged inside the active block scope boundaries
        while (1) {
            if (i->op == TAC_FUNC_START)       printf("    func %s:\n", i->dest);
            else if (i->op == TAC_LABEL)       printf("    %s:\n", i->dest);
            else if (i->op == TAC_ASSIGN)      printf("        %s = %s\n", i->dest, i->arg1);
            else if (i->op == TAC_ADD)         printf("        %s = %s + %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_SUB)         printf("        %s = %s - %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_MUL)         printf("        %s = %s * %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_DIV)         printf("        %s = %s / %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_LT)          printf("        %s = %s < %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_GT)          printf("        %s = %s > %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_EQ)          printf("        %s = %s == %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_NEQ)         printf("        %s = %s != %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_LE)          printf("        %s = %s <= %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_GE)          printf("        %s = %s >= %s\n", i->dest, i->arg1, i->arg2);
            else if (i->op == TAC_IF_FALSE)    printf("        if_false %s goto %s\n", i->arg1, i->dest);
            else if (i->op == TAC_GOTO)        printf("        goto %s\n", i->dest);
            else if (i->op == TAC_RETURN)      printf("        return %s\n", i->dest ? i->dest : "");

            if (i == b->end_instr) {
                break;
            }
            i = i->next;
        }

        // Trace and log route relationships linking the graph paths
        if (b->true_exit) {
            printf("  --> [True / Fallthrough Path] links to %s\n", b->true_exit->name);
        }
        if (b->false_exit) {
            printf("  --> [False / Branch Jump Path] links to %s\n", b->false_exit->name);
        }
        
        printf("\n");
        b = b->next;
    }
}



// Helper utility to convert a block's underlying TAC instructions into a formatted string block
void stringify_block_tac(BasicBlock *b, char *output_buffer) {

    output_buffer[0] = '\0';
    TACInstr *curr = b->start_instr;

    if (!curr) return;


    while (1) {
        char line_buffer[100] = {0};

        // Format the instruction text exactly like we do in print_tac()
        switch (curr->op) {
            case TAC_FUNC_START: sprintf(line_buffer, "func %s:\\n", curr->dest); break;
            case TAC_LABEL:      sprintf(line_buffer, "%s:\\n", curr->dest); break;
            case TAC_ASSIGN:     sprintf(line_buffer, "  %s = %s\\n", curr->dest, curr->arg1); break;
            case TAC_ADD:        sprintf(line_buffer, "  %s = %s + %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_SUB:        sprintf(line_buffer, "  %s = %s - %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_MUL:        sprintf(line_buffer, "  %s = %s * %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_DIV:        sprintf(line_buffer, "  %s = %s / %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_LT:         sprintf(line_buffer, "  %s = %s < %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_GT:         sprintf(line_buffer, "  %s = %s > %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_EQ:         sprintf(line_buffer, "  %s = %s == %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_NEQ:        sprintf(line_buffer, "  %s = %s != %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_LE:         sprintf(line_buffer, "  %s = %s <= %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_GE:         sprintf(line_buffer, "  %s = %s >= %s\\n", curr->dest, curr->arg1, curr->arg2); break;
            case TAC_IF_FALSE:   sprintf(line_buffer, "  if_false %s goto %s\\n", curr->arg1, curr->dest); break;
            case TAC_GOTO:       sprintf(line_buffer, "  goto %s\\n", curr->dest); break;
            case TAC_RETURN:     sprintf(line_buffer, "  return %s\\n", curr->dest ? curr->dest : ""); break;
            default: break;
        }

        strcat(output_buffer, line_buffer);

        if (curr == b->end_instr) {
            break;
        }
        curr = curr->next;
    }
}



// Walks your live basic block linked list and writes node/edge patterns into a clean JSON layout
void export_cfg_to_json(const char *filename) {

    FILE *fp = fopen(filename, "w");

    if (!fp) {
        return;
    }


    fprintf(fp, "{\n  \"nodes\": [\n");
    BasicBlock *curr = cfg_head;
    char tac_string_buffer[2000];


    // 1. Traverse and dump basic block metadata blocks along with their code text
    while (curr != NULL) {
        // Unpack this block's explicit instructions directly into our text collector string
        stringify_block_tac(curr, tac_string_buffer);

        fprintf(fp, "    {\"id\": \"%d\", \"label\": \"Block %d\\n%s\"}", 
                curr->id, curr->id, tac_string_buffer);
        
        if (curr->next != NULL) {
            fprintf(fp, ",");
        }
        fprintf(fp, "\n");
        curr = curr->next;
    }
    
    
    fprintf(fp, "  ],\n  \"edges\": [\n");
    curr = cfg_head;
    int first_edge = 1;
    
    // 2. Traverse again to trace route targets and build tracking paths
    while (curr != NULL) {
        
        if (curr->true_exit != NULL) {
            if (!first_edge) {
                fprintf(fp, ",\n");
            }
            fprintf(fp, "    {\"from\": \"%d\", \"to\": \"%d\", \"type\": \"true/fallthrough\"}", 
                    curr->id, curr->true_exit->id);
            first_edge = 0;
        }

        if (curr->false_exit != NULL) {
            if (!first_edge) {
                fprintf(fp, ",\n");
            }
            fprintf(fp, "    {\"from\": \"%d\", \"to\": \"%d\", \"type\": \"false/jump\"}", 
                    curr->id, curr->false_exit->id);
            first_edge = 0;
        }

        curr = curr->next;
    }
    
    fprintf(fp, "\n  ]\n}\n");
    fclose(fp);
}