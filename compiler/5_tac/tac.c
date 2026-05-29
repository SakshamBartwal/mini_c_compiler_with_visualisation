#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

TACInstr *tac_head = NULL;
TACInstr *tac_tail = NULL;

int temp_counter = 0;   
int label_counter = 0; 



// Generates a unique temporary variable string name (like t0, t1, t2...)
char* new_temp() {

    char *buf = malloc(20);
    sprintf(buf, "t%d", temp_counter++);
    
    return buf;
}



// Generates a unique branch label location string name (like L0, L1, L2...)
char* new_label() {

    char *buf = malloc(20);
    sprintf(buf, "L%d", label_counter++);
    
    return buf;
}



// Creates an instruction node and appends it to our global linear TAC list
void emit(TACOp op, const char *dest, const char *arg1, const char *arg2) {

    TACInstr *instr = malloc(sizeof(TACInstr));
    
    instr->op   = op;
    instr->dest = dest ? strdup(dest) : NULL;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->next = NULL;


    if (tac_head == NULL) {
        tac_head = instr;
        tac_tail = instr;
    } else {
        tac_tail->next = instr;
        tac_tail = instr;
    }
}



// Main recursive engine to translate your structural AST branches into flat linear code instructions
char* generate_tac(ASTNode *node) {

    if (node == NULL) {
        return NULL;
    }


    switch (node->type) {
        

        case NODE_FUNCTION_DEF: {

            emit(TAC_FUNC_START, node->value, NULL, NULL);
            
            if (node->left != NULL && node->left->type == NODE_COMPOUND_STATEMENT) {
                generate_tac(node->left->left);
            }

            break;
        }


        case NODE_DECLARATION: {

            generate_tac(node->left);
            break;
        }


        case NODE_IF: {

            // 1. Evaluate the conditional test first
            char *cond_val = generate_tac(node->left);
            char *label_else = new_label();
            char *label_end = new_label();

            // 2. Hop over to the alternative pathway block if the test fails
            emit(TAC_IF_FALSE, label_else, cond_val, NULL);

            // 3. Process the 'Then' positive block statements 
            generate_tac(node->right);

            // 4. Skip past the else body completely to exit cleanly
            emit(TAC_GOTO, label_end, NULL, NULL);

            // 5. Place down the alternative entry label location marker
            emit(TAC_LABEL, label_else, NULL, NULL);

            // 6. Process the alternative pathway body statements if they exist
            if (node->third != NULL) {
                generate_tac(node->third);
            }

            // 7. Establish the unified outer end anchor label location
            emit(TAC_LABEL, label_end, NULL, NULL);

            break;
        }


        case NODE_WHILE: {

            char *label_start = new_label();
            char *label_end = new_label();

            // 1. Put down the loop re-evaluation checkpoint marker at the top
            emit(TAC_LABEL, label_start, NULL, NULL);

            // 2. Resolve the conditional expression variable values
            char *cond_val = generate_tac(node->left);

            // 3. Fall out of the loop body completely if the condition breaks
            emit(TAC_IF_FALSE, label_end, cond_val, NULL);

            // 4. Translate and emit inner loop body contents
            generate_tac(node->right);

            // 5. Jump backward to re-run the loop evaluation criteria checks
            emit(TAC_GOTO, label_start, NULL, NULL);

            // 6. Anchor the permanent exit destination label location
            emit(TAC_LABEL, label_end, NULL, NULL);

            break;
        }


        case NODE_BINARY_OP: {

            // Intercept and redirect runtime function execution blueprints
            if (strcmp(node->value, "call") == 0) {
                if (node->right != NULL) {
                    generate_tac(node->right);
                }
                
                char *call_temp = new_temp();
                emit(TAC_ASSIGN, call_temp, node->left->value, NULL);
                
                return call_temp;
            }


            // Standard mathematical calculations and comparisons
            char *left_val = generate_tac(node->left);
            char *right_val = generate_tac(node->right);

            char *my_temp = new_temp();
            TACOp tac_op;


            if (strcmp(node->value, "+") == 0)       tac_op = TAC_ADD;
            else if (strcmp(node->value, "-") == 0)  tac_op = TAC_SUB;
            else if (strcmp(node->value, "*") == 0)  tac_op = TAC_MUL;
            else if (strcmp(node->value, "/") == 0)  tac_op = TAC_DIV;
            else if (strcmp(node->value, "<") == 0)  tac_op = TAC_LT;
            else if (strcmp(node->value, ">") == 0)  tac_op = TAC_GT;
            else if (strcmp(node->value, "==") == 0) tac_op = TAC_EQ;
            else if (strcmp(node->value, "!=") == 0) tac_op = TAC_NEQ;
            else if (strcmp(node->value, "<=") == 0) tac_op = TAC_LE;
            else if (strcmp(node->value, ">=") == 0) tac_op = TAC_GE;
            else return NULL;


            emit(tac_op, my_temp, left_val, right_val);
            
            return my_temp;
        }


        case NODE_ASSIGNMENT: {

            char *right_val = generate_tac(node->right);
            
            emit(TAC_ASSIGN, node->left->value, right_val, NULL);
            
            break;
        }


        case NODE_IDENTIFIER:
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL: {

            return strdup(node->value);
        }


        case NODE_RETURN: {

            if (node->left != NULL) {
                char *ret_val = generate_tac(node->left);
                emit(TAC_RETURN, ret_val, NULL, NULL);
            } else {
                emit(TAC_RETURN, NULL, NULL, NULL);
            }
            
            break;
        }


        default:
            generate_tac(node->left);
            generate_tac(node->right);
            generate_tac(node->third);
            break;
    }


    // Unconditionally evaluate horizontal sibling timelines next
    if (node->next != NULL) {
        generate_tac(node->next);
    }

    return NULL;
}



// Formats and prints out your full linear list of intermediate instructions onto the terminal dashboard
void print_tac() {

    printf("\n=========== Three-Address Code (TAC) ===========\n");
    TACInstr *curr = tac_head;


    while (curr != NULL) {
        switch (curr->op) {
            
            case TAC_FUNC_START:
                printf("func %s:\n", curr->dest);
                break;
                
            case TAC_LABEL:
                printf("%s:\n", curr->dest);
                break;
                
            case TAC_ASSIGN:
                printf("    %s = %s\n", curr->dest, curr->arg1);
                break;
                
            case TAC_ADD:
                printf("    %s = %s + %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_SUB:
                printf("    %s = %s - %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_MUL:
                printf("    %s = %s * %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_DIV:
                printf("    %s = %s / %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_IF_FALSE:
                printf("    if_false %s goto %s\n", curr->arg1, curr->dest);
                break;
                
            case TAC_GOTO:
                printf("    goto %s\n", curr->dest);
                break;
                
            case TAC_RETURN:
                printf("    return %s\n", curr->dest ? curr->dest : "");
                break;
                
            case TAC_LT:
                printf("    %s = %s < %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_GT:
                printf("    %s = %s > %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_EQ:
                printf("    %s = %s == %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_NEQ:
                printf("    %s = %s != %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_LE:
                printf("    %s = %s <= %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            case TAC_GE:
                printf("    %s = %s >= %s\n", curr->dest, curr->arg1, curr->arg2);
                break;
                
            default:
                break;
        }
        
        curr = curr->next;
    }
}