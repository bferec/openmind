
make lex.yy.c
make openmind.tab.c openmind.tab.h
make openmind.tab.o
make lex.yy.o
make openmindvarlist.o
make syntaxtree.o
make logicalOperator.o
make arithmeticOperator.o
make openmindinterpret.o
make openmindlib.o

gcc -o openmind openmind.c openmindlib.o openmindvarlist.o syntaxtree.o openmind.tab.o lex.yy.o arithmeticOperator.o logicalOperator.o openmindinterpret.o -lm
