
all: y.tab.c lex.yy.c
	gcc lex.yy.c y.tab.c -o main -lfl

y.tab.c: grammar.y
	yacc -d grammar.y 

lex.yy.c: flex.l 
	flex flex.l