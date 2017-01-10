rm -fr openmind y.tab.c lex.yy.c openmind.tab.h openmind.tab.c

bison -d openmind.y
flex *.l
gcc -o openmind openmind.tab.c lex.yy.c openmind.c openmindlib.c 
