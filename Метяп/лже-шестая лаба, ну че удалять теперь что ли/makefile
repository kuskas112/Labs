
all: main.c lex.yy.c tokens.h analyzer.h
	gcc main.c lex.yy.c tokens.h analyzer.h -o main -lfl

lex.yy.c: flex.l
	flex flex.l
