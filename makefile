all: openmind

openmind.tab.h: openmind.y openmindlib.h
	bison -d openmind.y

lex.yy.c: openmind.l openmind.tab.h
	flex openmind.l


openmind: lex.yy.c openmind.tab.c  openmind.c openmind.tab.h openmindlib.c openmindlib.h
	gcc -o openmind openmind.tab.c  lex.yy.c openmind.c openmindlib.c 

clean:
	rm openmind openmind.tab.c lex.yy.c openmind.tab.h
