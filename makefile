YACC = bison -d
LEX = flex
CC = gcc 
APPNAME = openmind

all: $(APPNAME)


$(APPNAME): $(APPNAME).tab.o lex.yy.o $(APPNAME)lib.o $(APPNAME)varlist.o syntaxtree.o $(APPNAME)interpret.o arithmeticOperator.o logicalOperator.o  $(APPNAME).c
	$(CC) -o $(APPNAME) $(APPNAME).c $(APPNAME)lib.c $(APPNAME)varlist.c  syntaxtree.c $(APPNAME).tab.o lex.yy.o arithmeticOperator.o logicalOperator.o $(APPNAME)interpret.c -lm

$(APPNAME)lib.o: $(APPNAME)lib.c $(APPNAME)lib.h
	$(CC) -c $(APPNAME)lib.c
	
$(APPNAME)Interpret.o: $(APPNAME)interpret.c $(APPNAME).tab.h $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h
	$(CC) -c $(APPNAME)interpret.c 

arithmeticOperator.o: arithmeticOperator.c arithmeticOperator.h $(APPNAME).tab.h $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h
	$(CC) -c arithmeticOperator.c 

logicalOperator.o: logicalOperator.c logicalOperator.h $(APPNAME).tab.h $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h expressions.h
	$(CC) -c logicalOperator.c 

syntaxtree.o: syntaxtree.c $(APPNAME)lib.h  entity.h openmindvalue.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h syntaxtree.h	
	$(CC) -c syntaxtree.c

openmindvarlist.o: openmindvarlist.c openmindlib.h entity.h openmindvalue.h openmindvarlist.h
	$(CC) -c openmindvarlist.c

lex.yy.o: lex.yy.c $(APPNAME).tab.h

$(APPNAME).tab.c $(APPNAME).tab.h: $(APPNAME).y $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h
	$(YACC) -v $(APPNAME).y

lex.yy.c: $(APPNAME).l  $(APPNAME).y $(APPNAME)lib.h entity.h $(APPNAME)value.h $(APPNAME)varlist.h $(APPNAME)constant.h operator.h
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
		[ -f "arithmeticOperator.o" ] 	&& rm arithmeticOperator.o; \
		[ -f "logicalOperator.o" ] 	&& rm logicalOperator.o; \
		[ -f "$(APPNAME)varlist.o" ]	&& rm $(APPNAME)varlist.o; \
		[ -f "$(APPNAME).output" ] 	&& rm $(APPNAME).output; \
		[ -f "$(APPNAME).err.txt" ] 	&& rm $(APPNAME).err.txt; \
		rm $(APPNAME).zip; \
		zip $(APPNAME).zip *; \


