
all: y.tab.c lex.yy.c
	gcc -w tree.c lex.yy.c y.tab.c -o main -lfl
	./main < input.txt

y.tab.c: grammar.y
	yacc -d -v grammar.y 

lex.yy.c: flex.l 
	flex flex.l