# Object configuration mappings
OBJS = lex.yy.o parser.tab.o compiler/3_ast/ast.o compiler/4_semantics/symbol_table.o compiler/4_semantics/semantic.o compiler/5_tac/tac.o compiler/6_cfg/cfg.o main.o
CFLAGS = -Wall -Wextra -I.

# Core compilation pipeline blueprint
compiler.exe: $(OBJS)
	gcc $(CFLAGS) -o compiler.exe $(OBJS)

lex.yy.c: compiler/1_lexer/lexer.l parser.tab.h
	flex compiler/1_lexer/lexer.l

parser.tab.c parser.tab.h: compiler/2_parser/parser.y
	bison -d compiler/2_parser/parser.y

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

compiler/3_ast/ast.o: compiler/3_ast/ast.c
	gcc $(CFLAGS) -c compiler/3_ast/ast.c -o compiler/3_ast/ast.o

compiler/4_semantics/symbol_table.o: compiler/4_semantics/symbol_table.c
	gcc $(CFLAGS) -c compiler/4_semantics/symbol_table.c -o compiler/4_semantics/symbol_table.o

compiler/4_semantics/semantic.o: compiler/4_semantics/semantic.c
	gcc $(CFLAGS) -c compiler/4_semantics/semantic.c -o compiler/4_semantics/semantic.o

compiler/5_tac/tac.o: compiler/5_tac/tac.c compiler/5_tac/tac.h
	gcc $(CFLAGS) -c compiler/5_tac/tac.c -o compiler/5_tac/tac.o

# === NEW CFG COMPILATION DIRECTIVE TARGET ===
compiler/6_cfg/cfg.o: compiler/6_cfg/cfg.c compiler/6_cfg/cfg.h
	gcc $(CFLAGS) -c compiler/6_cfg/cfg.c -o compiler/6_cfg/cfg.o

main.o: compiler/main.c
	gcc $(CFLAGS) -c compiler/main.c -o main.o

# Clean up build residue footprint contexts
clean:
	rm -f *.o lex.yy.c parser.tab.c parser.tab.h compiler.exe
	rm -f compiler/3_ast/*.o
	rm -f compiler/4_semantics/*.o
	rm -f compiler/5_tac/*.o
	rm -f compiler/6_cfg/*.o

rebuild: clean compiler.exe