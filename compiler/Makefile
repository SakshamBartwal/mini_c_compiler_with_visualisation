all:
	bison -d parser.y
	flex lexer.l
	gcc lex.yy.c parser.tab.c symbol_table.c -o compiler
	
run:
	./compiler < test.c

clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h compiler