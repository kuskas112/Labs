

all: main.c lex.yy.c analyzer.h tokens.h parse_tables.h
	gcc main.c lex.yy.c analyzer.h tokens.h parse_tables.h -o main -lfl

lex.yy.c: flex.l
	flex flex.l