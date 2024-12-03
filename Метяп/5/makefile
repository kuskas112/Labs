

all: main.c lex.yy.c analyzer.h tokens.h parse_tables.h stack.h
	gcc main.c lex.yy.c analyzer.h tokens.h parse_tables.h stack.h -o main -lfl

lex.yy.c: flex.l
	flex flex.l