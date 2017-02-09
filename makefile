YACC = bison -d -v 
LEX = flex
CC = gcc 
APPNAME = openmind
LDFLAGS = -lm

.PHONY: clean all

all: $(APPNAME)

$(APPNAME): $(APPNAME).c $(APPNAME)lib.o $(APPNAME)interpret.o iterOperator.o IncrDecrOperator.o assignationOperator.o arithmeticOperator.o comparaisonOperator.o logicalOperator.o syntaxtree.o $(APPNAME)varlist.o $(APPNAME)EntityList.o $(APPNAME)PropertyList.o lex.yy.o $(APPNAME).tab.o 
	$(CC) -o $(APPNAME) $(APPNAME).c $(APPNAME)lib.o $(APPNAME)varlist.o $(APPNAME)EntityList.o  $(APPNAME)PropertyList.o syntaxtree.o debugTools.o $(APPNAME).tab.o lex.yy.o arithmeticOperator.o logicalOperator.o comparaisonOperator.o assignationOperator.o IncrDecrOperator.o iterOperator.o  alternatOperator.o binaryOperator.o $(APPNAME)interpret.o  -lm

$(APPNAME)lib.o: $(APPNAME)lib.c $(APPNAME)lib.h
	$(CC) -c $(APPNAME)lib.c
 	
$(APPNAME)interpret.o: $(APPNAME)interpret.c $(APPNAME).tab.h $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h logicalOperator.h arithmeticOperator.h comparaisonOperator.h assignationOperator.h IncrDecrOperator.h iterOperator.h binaryOperator.h alternatOperator.h syntaxtree.h expressions.h
	$(CC) -c $(APPNAME)interpret.c 

binaryOperator.o: binaryOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h
	$(CC) -c binaryOperator.c 

alternatOperator.o: alternatOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h
	$(CC) -c alternatOperator.c 

iterOperator.o: iterOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h
	$(CC) -c iterOperator.c 

IncrDecrOperator.o: IncrDecrOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h
	$(CC) -c IncrDecrOperator.c 
	
assignationOperator.o: assignationOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h
	$(CC) -c assignationOperator.c 
	
arithmeticOperator.o: arithmeticOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h
	$(CC) -c arithmeticOperator.c 
	
comparaisonOperator.o: comparaisonOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h   
	$(CC) -c comparaisonOperator.c 

logicalOperator.o: logicalOperator.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h $(APPNAME).tab.h   
	$(CC) -c logicalOperator.c 
	
syntaxtree.o: syntaxtree.c $(APPNAME)lib.h  entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h	$(APPNAME).tab.h
	$(CC) -c syntaxtree.c

debugTools.o: debugTools.c 
	$(CC) -c debugTools.c
	
$(APPNAME)varlist.o: $(APPNAME)varlist.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h
	$(CC) -c $(APPNAME)varlist.c

$(APPNAME)EntityList.o: $(APPNAME)EntityList.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h
	$(CC) -c $(APPNAME)EntityList.c

$(APPNAME)PropertyList.o: $(APPNAME)PropertyList.c $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h
	$(CC) -c $(APPNAME)PropertyList.c
	
lex.yy.o: lex.yy.c $(APPNAME).tab.h
	$(CC) -c lex.yy.c

$(APPNAME).tab.o: $(APPNAME).tab.c
	$(CC) -c $(APPNAME).tab.c

$(APPNAME).tab.c $(APPNAME).tab.h: $(APPNAME).y $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h  expressions.h 
	$(YACC) $(APPNAME).y 
	
lex.yy.c: $(APPNAME).l  $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h
	$(LEX) $(APPNAME).l

	
clean:
		[ -f "$(APPNAME)" ] 			&& rm $(APPNAME); \
		[ -f "$(APPNAME).tab.o" ] 		&& rm $(APPNAME).tab.o; \
		[ -f "$(APPNAME).tab.c" ] 		&& rm $(APPNAME).tab.c; \
		[ -f "$(APPNAME).tab.h" ] 		&& rm $(APPNAME).tab.h; \
		[ -f "lex.yy.o" ] 			&& rm lex.yy.o; \
		[ -f "lex.yy.c" ] 			&& rm lex.yy.c; \
		[ -f "$(APPNAME)lib.o" ] 		&& rm $(APPNAME)lib.o; \
		[ -f "$(APPNAME)interpret.o" ]		&& rm $(APPNAME)interpret.o; \
		[ -f "syntaxtree.o" ] 			&& rm syntaxtree.o; \
		[ -f "debugTools.o" ] 			&& rm debugTools.o; \
		[ -f "arithmeticOperator.o" ] 		&& rm arithmeticOperator.o; \
		[ -f "logicalOperator.o" ] 		&& rm logicalOperator.o; \
		[ -f "comparaisonOperator.o" ] 		&& rm comparaisonOperator.o; \
		[ -f "assignationOperator.o" ] 		&& rm assignationOperator.o; \
		[ -f "IncrDecrOperator.o" ] 		&& rm IncrDecrOperator.o; \
		[ -f "iterOperator.o" ] 		&& rm iterOperator.o; \
		[ -f "alternatOperator.o" ] 		&& rm alternatOperator.o; \
		[ -f "binaryOperator.o" ] 		&& rm binaryOperator.o; \
		[ -f "$(APPNAME)varlist.o" ]		&& rm $(APPNAME)varlist.o; \
		[ -f "$(APPNAME)EntityList.o" ]		&& rm $(APPNAME)EntityList.o; \
		[ -f "$(APPNAME)PropertyList.o" ]	&& rm $(APPNAME)PropertyList.o; \
		[ -f "$(APPNAME).output" ] 		&& rm $(APPNAME).output; \
		[ -f "$(APPNAME).err.txt" ] 		&& rm $(APPNAME).err.txt; \
		rm $(APPNAME).zip; \
		zip $(APPNAME).zip *; \


