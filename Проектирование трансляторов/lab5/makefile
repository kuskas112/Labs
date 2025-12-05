
all: main
	./main < input.txt

main: y.tab.o lex.yy.o tree.o SECD.o
	g++ -g -O0 lex.yy.o y.tab.o tree.o SECD.o -o main

SECD.o: SECD.cpp
	g++ -g -c SECD.cpp

tree.o:	tree.c
	gcc -g -c tree.c

y.tab.o: y.tab.c
	gcc -g -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -g -c lex.yy.c

y.tab.c: grammar.y
	yacc -d grammar.y

lex.yy.c: flex.l
	flex flex.l