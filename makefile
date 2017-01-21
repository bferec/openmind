YACC = bison -d
LEX = flex
CC = gcc
APPNAME = openmind

all: $(APPNAME)


$(APPNAME): $(APPNAME).tab.o lex.yy.o $(APPNAME)lib.o syntaxtree.o $(APPNAME)interpret.o
	$(CC) -o $(APPNAME) $(APPNAME).c $(APPNAME)lib.c  syntaxtree.c  $(APPNAME).tab.o lex.yy.o  $(APPNAME)interpret.c -lm

$(APPNAME)lib.o: $(APPNAME)lib.c $(APPNAME)lib.h
	$(CC) -c $(APPNAME)lib.c
	
$(APPNAME)Interpret.o: $(APPNAME)interpret.c $(APPNAME).tab.h
	$(CC) -c $(APPNAME)interpret.c

syntaxtree.o: syntaxtree.c $(APPNAME)lib.h	
	$(CC) -c syntaxtree.c

lex.yy.o: lex.yy.c $(APPNAME).tab.h

$(APPNAME).tab.c $(APPNAME).tab.h: $(APPNAME).y
	$(YACC) -v $(APPNAME).y

lex.yy.c: $(APPNAME).l
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
		[ -f "$(APPNAME).output" ] 	&& rm $(APPNAME).output; \
		rm $(APPNAME).zip; \
		zip $(APPNAME).zip *; \



