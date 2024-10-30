
all: main.c lex.yy.c tokens.h
	gcc main.c lex.yy.c tokens.h -o main -lfl

lex.yy.c: flex.l
	flex flex.l
