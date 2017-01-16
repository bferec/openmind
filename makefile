YACC = bison -d
LEX = flex
CC = gcc

all: openmind


openmind: openmind.tab.o lex.yy.o
	$(CC) -o openmind openmind.c openmindlib.c  openmind.tab.o lex.yy.o -lm

openmindlib.o: openmindlib.c openmindlib.h
	
lex.yy.o: lex.yy.c openmind.tab.h

openmind.tab.c openmind.tab.h: openmind.y
	$(YACC) -v openmind.y

lex.yy.c: openmind.l
	$(LEX) openmind.l

clean:
	rm openmind openmind.tab.c lex.yy.c openmind.tab.h *.output *.o
