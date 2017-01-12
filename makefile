YACC = bison -d
LEX = flex
CC = gcc

all: openmind


openmind: openmind.tab.o lex.yy.o
		$(CC) -o openmind  openmind.tab.o lex.yy.o -ll -lm

lex.yy.o: lex.yy.c openmind.tab.h
lex.yy.o openmind.tab.o: openmind.h

openmind.tab.c openmind.tab.h: openmind.y
		$(YACC) -v openmind.y

lex.yy.c: openmind.l
		$(LEX) openmind.l

clean:
	rm openmind openmind.tab.c lex.yy.c openmind.tab.h
