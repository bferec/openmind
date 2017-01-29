YACC = bison -d -v 
LEX = flex
CC = gcc 
APPNAME = openmind
LDFLAGS = -lm

.PHONY: clean all



all: $(APPNAME)

$(APPNAME): $(APPNAME).c $(APPNAME)lib.o $(APPNAME)varlist.o syntaxtree.o arithmeticOperator.o logicalOperator.o  comparaisonOperator.o $(APPNAME)interpret.o lex.yy.o $(APPNAME).tab.o
	$(CC) $(LDFLAGS) -o fdl.c $(APPNAME)lib.o $(APPNAME)varlist.o syntaxtree.o arithmeticOperator.o logicalOperator.o comparaisonOperator.o  $(APPNAME)interpret.o lex.yy.o $(APPNAME).tab.o

$(APPNAME)lib.o: $(APPNAME)lib.c $(APPNAME)lib.h
	$(CC) -c $(APPNAME)lib.c
 	
$(APPNAME)interpret.o: $(APPNAME)interpret.c $(APPNAME).tab.h $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h logicalOperator.h arithmeticOperator.h comparaisonOperator.h syntaxtree.h expressions.h
	$(CC) -c $(APPNAME)interpret.c 

	
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

	
lex.yy.o: lex.yy.c $(APPNAME).tab.h
	$(CC) -c lex.yy.c

	
$(APPNAME).tab.o: $(APPNAME).tab.c
	$(CC) -c $(APPNAME).tab.c

	
$(APPNAME).tab.c $(APPNAME).tab.h: $(APPNAME).y $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h  expressions.h 
	$(YACC) $(APPNAME).y 

	
lex.yy.c: $(APPNAME).l  $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h
	$(LEX) $(APPNAME).l

	
clean:
		[ -f "$(APPNAME)" ] 		&& rm $(APPNAME); \
		[ -f "$(APPNAME).tab.o" ] 	&& rm $(APPNAME).tab.o; \
		[ -f "$(APPNAME).tab.c" ] 	&& rm $(APPNAME).tab.c; \
		[ -f "$(APPNAME).tab.h" ] 	&& rm $(APPNAME).tab.h; \
		[ -f "lex.yy.o" ] 		&& rm lex.yy.o; \
		[ -f "lex.yy.c" ] 		&& rm lex.yy.c; \
		[ -f "$(APPNAME)lib.o" ] 	&& rm $(APPNAME)lib.o; \
		[ -f "$(APPNAME)interpret.o" ]	&& rm $(APPNAME)interpret.o; \
		[ -f "syntaxtree.o" ] 		&& rm syntaxtree.o; \
		[ -f "debugTools.o" ] 		&& rm debugTools.o; \
		[ -f "arithmeticOperator.o" ] 	&& rm arithmeticOperator.o; \
		[ -f "logicalOperator.o" ] 	&& rm logicalOperator.o; \
		[ -f "comparaisonOperator.o" ] 	&& rm comparaisonOperator.o; \
		[ -f "$(APPNAME)varlist.o" ]	&& rm $(APPNAME)varlist.o; \
		[ -f "$(APPNAME).output" ] 	&& rm $(APPNAME).output; \
		[ -f "$(APPNAME).err.txt" ] 	&& rm $(APPNAME).err.txt; \
		rm $(APPNAME).zip; \
		zip $(APPNAME).zip *; \


