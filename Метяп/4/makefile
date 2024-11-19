
all: main.c lex.yy.c stack.h tokens.h analyzer.h
	gcc main.c lex.yy.c stack.h tokens.h analyzer.h -o main -lfl

debug: main.c lex.yy.c stack.h tokens.h analyzer.h
	gcc -g main.c lex.yy.c stack.h tokens.h analyzer.h -o mainDebug -lfl

lex.yy.c: flex.l
	flex flex.l
