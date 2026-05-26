%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int line_num;

void yyerror(const char *s);
%}

%union {
    int ival;
    float fval;
    char* sval;
}

%token IMPORT
%token INT FLOAT CHAR VOID
%token IF ELSE WHILE FOR RETURN
%token SWITCH CASE DEFAULT
%token BREAK CONTINUE

%token EQ NEQ LE GE AND OR

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL
%token <sval> IDENTIFIER

%left OR
%left AND
%left EQ NEQ
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/'

%%

program:
      program external_declaration
    |
    ;

external_declaration:
      function_definition
    | declaration
    | import_statement
    ;

import_statement:
      IMPORT STRING_LITERAL ';'
      {
          printf("Import detected: %s\n", $2);
      }
    ;

function_definition:
      type_specifier IDENTIFIER '(' parameter_list ')' compound_statement
      {
          printf("Function defined: %s\n", $2);
      }
    ;

parameter_list:
      parameter_list ',' parameter
    | parameter
    |
    ;

parameter:
      type_specifier IDENTIFIER
    ;

declaration:
      type_specifier variable_list ';'
    ;

variable_list:
      variable_list ',' variable
    | variable
    ;

variable:
      IDENTIFIER
      {
          printf("Variable declared: %s\n", $1);
      }
    |
      IDENTIFIER '=' expression
      {
          printf("Variable initialized: %s\n", $1);
      }
    ;

compound_statement:
      '{' statement_list '}'
    ;

statement_list:
      statement_list statement
    |
    ;

statement:
      declaration
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | compound_statement
    ;

expression_statement:
      expression ';'
    | ';'
    ;

selection_statement:
      IF '(' expression ')' statement
    | IF '(' expression ')' statement ELSE statement
    ;

iteration_statement:
      WHILE '(' expression ')' statement
    | FOR '(' expression_statement expression_statement expression ')' statement
    ;

jump_statement:
      RETURN expression ';'
    | BREAK ';'
    | CONTINUE ';'
    ;

expression:
      expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | expression EQ expression
    | expression NEQ expression
    | expression LE expression
    | expression GE expression
    | IDENTIFIER '=' expression
    | IDENTIFIER
    | INT_LITERAL
    | FLOAT_LITERAL
    | STRING_LITERAL
    | '(' expression ')'
    ;

type_specifier:
      INT
    | FLOAT
    | CHAR
    | VOID
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s at line %d\n", s, line_num);
}

int main() {
    printf("Starting compilation...\n");

    yyparse();

    printf("Compilation finished.\n");

    return 0;
}