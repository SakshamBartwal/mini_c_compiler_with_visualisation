%{
#include "compiler/3_ast/ast.h"
#include "parser.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
extern char current_file[100];

// Keeps track of parent file buffers when handling nested imports (up to 10 deep)
#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

// Remembers line numbers and names of parent files so error reports stay accurate
int line_num_stack[MAX_INCLUDE_DEPTH];
char file_name_stack[MAX_INCLUDE_DEPTH][100];
%}

%x COMMENT
%x IMPORT_STATE

DIGIT          [0-9]
LETTER         [a-zA-Z_]
ID             {LETTER}({LETTER}|{DIGIT})*

NUMBER         {DIGIT}+
FLOATNUM       {DIGIT}+\.{DIGIT}+

STRING         \"([^\\\"]|\\.)*\"

%%

 /* =========================================================
       PREPROCESSOR / IMPORTS
    ========================================================= */

"import"               { BEGIN(IMPORT_STATE); }

<IMPORT_STATE>[ \t\r]* /* strip spaces inside the import statement */ ;

<IMPORT_STATE>{STRING}[ \t\r]*";" {
    // Strip the opening quote from the filename
    char *filename = strdup(yytext + 1);
    
    // Find the closing quote and cut the string off there
    char *end_quote = strchr(filename, '"');
    if (end_quote) *end_quote = '\0';

    // Prevent infinite import loops from crashing the compiler stack
    if (include_stack_ptr >= MAX_INCLUDE_DEPTH) {
        fprintf(stderr, "Lexer Error: Imports nested too deeply (Max Limit: %d)\n", MAX_INCLUDE_DEPTH);
        exit(1);
    }

    // Try to open the imported sub-file
    FILE *inc = fopen(filename, "r");
    if (!inc) {
        fprintf(stderr, "%s: Lexer Error: Cannot open import file '%s' at line %d\n", current_file, filename, line_num);
        exit(1);
    }

    // Save the current file's parsing state onto our tracker stack
    line_num_stack[include_stack_ptr] = line_num;
    strcpy(file_name_stack[include_stack_ptr], current_file);
    include_stack[include_stack_ptr] = YY_CURRENT_BUFFER;
    include_stack_ptr++;

    // Reset tracking indicators for the newly discovered file
    line_num = 1;
    strncpy(current_file, filename, sizeof(current_file) - 1);

    // Swap Flex's active reading context to parse the child file
    yy_switch_to_buffer(yy_create_buffer(inc, YY_BUF_SIZE));

    free(filename);
    BEGIN(INITIAL); // Return straight to parsing normal C code inside the sub-file
}

<IMPORT_STATE>.|\n { 
    fprintf(stderr, "%s: Lexer Error: Malformed import syntax at line %d\n", current_file, line_num); 
    exit(1); 
}


 /* =========================================================
       KEYWORDS
    ========================================================= */

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


 /* =========================================================
       MULTI-CHARACTER OPERATORS
       (Must sit above single-character operators to match correctly)
    ========================================================= */

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


 /* =========================================================
       LITERALS
    ========================================================= */

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


 /* =========================================================
       IDENTIFIERS (Variable and Function names)
    ========================================================= */

{ID}                   {
                            yylval.sval = strdup(yytext);
                            return IDENTIFIER;
                        }


 /* =========================================================
       SINGLE-CHARACTER OPERATORS
    ========================================================= */

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


 /* =========================================================
       COMMENTS
    ========================================================= */

"//".* ;               // Skip single-line comments completely

"/*"                    { BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>\n             { line_num++; }
<COMMENT>.              ;   


 /* =========================================================
       WHITESPACE
    ========================================================= */

[ \t\r]+               ;
\n                     { line_num++; }


 /* =========================================================
       ERROR HANDLING
    ========================================================= */

.                      {
                            fprintf(
                                stderr,
                                "%s: Lexical Error: Unknown character '%s' at line %d\n",
                                current_file,
                                yytext,
                                line_num
                            );
                        }

%%

// Automatically called by Flex when it hits the End-Of-File marker
int yywrap() {
    // If our history stack is empty, we are completely done parsing the project
    if (include_stack_ptr <= 0) {
        return 1;
    }

    // Safely clear out the completed file buffer from memory
    yy_delete_buffer(YY_CURRENT_BUFFER);
    include_stack_ptr--;

    // Pop the parent file details off our history tracker
    line_num = line_num_stack[include_stack_ptr];
    strcpy(current_file, file_name_stack[include_stack_ptr]);

    // Re-activate the parent file buffer to resume reading where we left off
    yy_switch_to_buffer(include_stack[include_stack_ptr]);
    
    return 0; // Tells Flex to seamlessly keep reading from the parent file
}