
make lex.yy.c
make openmind.tab.c openmind.tab.h
make openmind.tab.o
make lex.yy.o

make openmindvarlist.o
make openmindPropertyList.o 
make openmindEntityList.o 

make syntaxtree.o
make debugTools.o

make comparaisonOperator.o
make logicalOperator.o
make assignationOperator.o
make arithmeticOperator.o
make IncrDecrOperator.o
make iterOperator.o
make binaryOperator.o
make alternatOperator.o

make openmindinterpret.o
make openmindlib.o
make openmindConfig.o

gcc -o openmind openmind.c openmindConfig.o openmindlib.o openmindvarlist.o openmindEntityList.o  openmindPropertyList.o syntaxtree.o debugTools.o openmind.tab.o lex.yy.o arithmeticOperator.o logicalOperator.o comparaisonOperator.o assignationOperator.o IncrDecrOperator.o iterOperator.o binaryOperator.o alternatOperator.o openmindinterpret.o  -lm
