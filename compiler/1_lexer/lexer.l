%{
#include "compiler/3_ast/ast.h"
#include "parser.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
extern char current_file[100];

/* File-Switching Buffer Stack Configurations */
#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

/* Save line numbers of parent files so line errors stay accurate */
int line_num_stack[MAX_INCLUDE_DEPTH];
char file_name_stack[MAX_INCLUDE_DEPTH][100];
%}

%x COMMENT
/* Removed %option noyywrap to let our custom yywrap handle EOF stack switching */

%x IMPORT_STATE

DIGIT          [0-9]
LETTER         [a-zA-Z_]
ID             {LETTER}({LETTER}|{DIGIT})*

NUMBER         {DIGIT}+
FLOATNUM       {DIGIT}+\.{DIGIT}+

STRING         \"([^\\\"]|\\.)*\"

%%

 /*|=========================================================|
   |                    PREPROCESSOR / IMPORTS               |
   |=========================================================| */

"import"               { BEGIN(IMPORT_STATE); }

<IMPORT_STATE>[ \t\r]* /* skip structural space */ ;

<IMPORT_STATE>{STRING}[ \t\r]*";" {
    /* Extract the file path string, accounting for the trailing semicolon matched above */
    char *filename = strdup(yytext + 1);
    
    /* Find where the closing quote is to strip it cleanly */
    char *end_quote = strchr(filename, '"');
    if (end_quote) *end_quote = '\0';

    if (include_stack_ptr >= MAX_INCLUDE_DEPTH) {
        fprintf(stderr, "Lexer Error: Imports nested too deeply (Max Limit: %d)\n", MAX_INCLUDE_DEPTH);
        exit(1);
    }

    FILE *inc = fopen(filename, "r");
    if (!inc) {
        fprintf(stderr, "%s: Lexer Error: Cannot open import file '%s' at line %d\n", current_file, filename, line_num);
        exit(1);
    }

    /* Save the current state before switching */
    line_num_stack[include_stack_ptr] = line_num;
    strcpy(file_name_stack[include_stack_ptr], current_file);
    include_stack[include_stack_ptr] = YY_CURRENT_BUFFER;
    include_stack_ptr++;

    /* Update current tracking metadata for the sub-file */
    line_num = 1;
    strncpy(current_file, filename, sizeof(current_file) - 1);

    /* Switch Flex's active character stream context to the sub-file */
    yy_switch_to_buffer(yy_create_buffer(inc, YY_BUF_SIZE));

    free(filename);
    BEGIN(INITIAL); /* Drop directly back to parsing code inside the sub-file */
}

<IMPORT_STATE>.|\n      { fprintf(stderr, "%s: Lexer Error: Malformed import syntax at line %d\n", current_file, line_num); exit(1); }


 /*|=========================================================|
   |                         KEYWORDS                        |
   |=========================================================| */

"int"                  { return INT; }
"float"                { return FLOAT; }
"char"                 { return CHAR; }
"void"                 { return VOID; }

"double"               { return DOUBLE; }

"long"                 { return LONG; }
"short"                { return SHORT; }
"signed"               { return SIGNED; }
"unsigned"             { return UNSIGNED; }

"if"                   { return IF; }
"else"                 { return ELSE; }

"while"                { return WHILE; }
"for"                  { return FOR; }
"do"                   { return DO; }

"return"               { return RETURN; }

"switch"               { return SWITCH; }
"case"                 { return CASE; }
"default"              { return DEFAULT; }

"break"                { return BREAK; }
"continue"             { return CONTINUE; }

"sizeof"               { return SIZEOF; }


 /*|=========================================================|
   |                  MULTI-CHAR OPERATORS                   |
   |---------------------------------------------------------|
   |           Must appear BEFORE single-char operators      |
   |=========================================================| */

"=="                   { return EQ; }
"!="                   { return NEQ; }

"<="                   { return LE; }
">="                   { return GE; }

"&&"                   { return AND; }
"||"                   { return OR; }

"++"                   { return INC; }
"--"                   { return DEC; }

"+="                   { return ADD_ASSIGN; }
"-="                   { return SUB_ASSIGN; }
"*="                   { return MUL_ASSIGN; }
"/="                   { return DIV_ASSIGN; }


 /*|=========================================================|
   |                         LITERALS                        |
   |=========================================================|*/

{FLOATNUM}             {
                            yylval.sval = strdup(yytext);
                            return FLOAT_LITERAL;
                        }

{NUMBER}               {
                            yylval.sval = strdup(yytext);
                            return INT_LITERAL;
                        }

{STRING}               {
                            yylval.sval = strdup(yytext);
                            return STRING_LITERAL;
                        }


 /*|=========================================================|
   |                        IDENTIFIERS                      |
   |=========================================================|*/

{ID}                   {
                            yylval.sval = strdup(yytext);
                            return IDENTIFIER;
                        }


 /*|=========================================================|
   |                  SINGLE-CHAR OPERATORS                  |
   |=========================================================|*/

"+"                    { return '+'; }
"-"                    { return '-'; }

"*"                    { return '*'; }
"/"                    { return '/'; }
"%"                    { return '%'; }

"="                    { return '='; }

"<"                    { return '<'; }
">"                    { return '>'; }

"!"                    { return '!'; }

"&"                    { return '&'; }

"?"                    { return '?'; }
":"                    { return ':'; }

";"                    { return ';'; }
","                    { return ','; }

"("                    { return '('; }
")"                    { return ')'; }

"{"                    { return '{'; }
"}"                    { return '}'; }

"["                    { return '['; }
"]"                    { return ']'; }


 /*|=========================================================|
   |                         COMMENTS                        |
   |=========================================================|*/

"//".* ;   /* Single-line comments */

"/*"                    { BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>\n             { line_num++; }
<COMMENT>.              ;   


 /*|=========================================================|
   |                        WHITESPACE                       |
   |=========================================================|*/

[ \t\r]+               ;
\n                     { line_num++; }


 /*|=========================================================|
   |                      ERROR HANDLING                     |
   |=========================================================|*/

.                      {fprintf(
                            stderr,
                            "%s: Lexical Error: Unknown character '%s' at line %d\n",
                            current_file,
                            yytext,
                            line_num
                        );}

%%

/* Custom EOF switch wrap controller */
int yywrap() {
    if (include_stack_ptr <= 0) {
        return 1; /* Stack is empty: truly terminate the lexer stream */
    }

    /* Clean up the current complete buffer stream */
    yy_delete_buffer(YY_CURRENT_BUFFER);
    include_stack_ptr--;

    /* Restore parent metadata context logs */
    line_num = line_num_stack[include_stack_ptr];
    strcpy(current_file, file_name_stack[include_stack_ptr]);

    /* Switch context back to the parent file buffer */
    yy_switch_to_buffer(include_stack[include_stack_ptr]);
    
    return 0; /* Tell Flex to keep parsing the popped file */
}