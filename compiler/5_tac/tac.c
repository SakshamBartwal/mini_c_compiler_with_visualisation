#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

TACInstr *tac_head = NULL;
TACInstr *tac_tail = NULL;

int temp_counter = 0;   
int label_counter = 0; /* Tracks L0, L1, L2... */

char* new_temp() {
    char *buf = malloc(20);
    sprintf(buf, "t%d", temp_counter++);
    return buf;
}

/* === ADD THIS LABEL GENERATOR === */
char* new_label() {
    char *buf = malloc(20);
    sprintf(buf, "L%d", label_counter++);
    return buf;
}

void emit(TACOp op, const char *dest, const char *arg1, const char *arg2) {
    TACInstr *instr = malloc(sizeof(TACInstr));
    instr->op = op;
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

char* generate_tac(ASTNode *node) {
    if (node == NULL) return NULL;

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

        /* === NEW CONTROL FLOW CASES === */
        case NODE_IF: {
            /* 1. Evaluate condition expression */
            char *cond_val = generate_tac(node->left);
            char *label_else = new_label();
            char *label_end = new_label();

            /* 2. Jump to else marker if the condition is false */
            emit(TAC_IF_FALSE, label_else, cond_val, NULL);

            /* 3. Process the 'Then' true block */
            generate_tac(node->right);

            /* 4. Jump past the else block entirely */
            emit(TAC_GOTO, label_end, NULL, NULL);

            /* 5. Emit Else label anchor location */
            emit(TAC_LABEL, label_else, NULL, NULL);

            /* 6. Process 'Else' false block if it exists (node->third) */
            if (node->third != NULL) {
                generate_tac(node->third);
            }

            /* 7. Emit End label anchor location */
            emit(TAC_LABEL, label_end, NULL, NULL);
            break;
        }

        case NODE_WHILE: {
            char *label_start = new_label();
            char *label_end = new_label();

            /* 1. Anchor top evaluation loop position */
            emit(TAC_LABEL, label_start, NULL, NULL);

            /* 2. Resolve conditional expression variables */
            char *cond_val = generate_tac(node->left);

            /* 3. Fall out of loop if expression evaluates to false */
            emit(TAC_IF_FALSE, label_end, cond_val, NULL);

            /* 4. Execute repetitive code contents */
            generate_tac(node->right);

            /* 5. Perform backward loop jump to restart re-evaluation */
            emit(TAC_GOTO, label_start, NULL, NULL);

            /* 6. Anchor exit destination loop position */
            emit(TAC_LABEL, label_end, NULL, NULL);
            break;
        }

        case NODE_BINARY_OP: {
            /* 1. INTERCEPT FUNCTION CALL BLUEPRINTS */
            if (strcmp(node->value, "call") == 0) {
                if (node->right != NULL) {
                    generate_tac(node->right);
                }
                char *call_temp = new_temp();
                emit(TAC_ASSIGN, call_temp, node->left->value, NULL);
                return call_temp;
            }

            /* 2. NORMAL OPERATIONAL ENGINE (MATH & COMPARISONS) */
            char *left_val = generate_tac(node->left);
            char *right_val = generate_tac(node->right);

            char *my_temp = new_temp();

            TACOp tac_op;
            if (strcmp(node->value, "+") == 0) tac_op = TAC_ADD;
            else if (strcmp(node->value, "-") == 0) tac_op = TAC_SUB;
            else if (strcmp(node->value, "*") == 0) tac_op = TAC_MUL;
            else if (strcmp(node->value, "/") == 0) tac_op = TAC_DIV;
            /* === ADD RELATIONAL OPERATOR MATCHERS HERE === */
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

    if (node->next != NULL) {
        generate_tac(node->next);
    }
    return NULL;
}

/* Update your printing switch to render labels and jumps */
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
            /* === ADD THESE MATCHERS INSIDE THE SWITCH OF PRINT_TAC === */
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