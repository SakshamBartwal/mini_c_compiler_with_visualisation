CC = gcc
CFLAGS = -Wall -Wextra

BISON = bison
FLEX = flex

TARGET = compiler.exe

LEXER = compiler/1_lexer/lexer.l
PARSER = compiler/2_parser/parser.y

AST = compiler/3_ast/ast.c
MAIN = compiler/main.c

all: $(TARGET)

$(TARGET): parser.tab.c lex.yy.c
	$(CC) $(CFLAGS) parser.tab.c lex.yy.c $(AST) $(MAIN) -o $(TARGET)

parser.tab.c parser.tab.h: $(PARSER)
	$(BISON) -d $(PARSER)

lex.yy.c: $(LEXER) parser.tab.h
	$(FLEX) $(LEXER)

run:
	./$(TARGET) $(FILE)

clean:
	rm -f $(TARGET) lex.yy.c parser.tab.c parser.tab.h

rebuild: clean all