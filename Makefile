target: parser

OBJS=func.o linkedlist.o verticeList.o

lex.yy.c: parser.l parser.tab.h
	flex parser.l

parser.tab.c parser.tab.h: parser.y
	bison -v -d parser.y

parser: lex.yy.c $(OBJS)
	gcc -g -o $@ parser.tab.c lex.yy.c $(OBJS) -lfl

func.o: func.c func.h
	gcc -g -Wall -c func.c

linkedlist.o: linkedlist.c linkedlist.h
	gcc -g -Wall -c linkedlist.c

verticeList.o: verticeList.c verticeList.h
	gcc -g -Wall -c verticeList.c

clear:
	rm -rf parser lex.yy.c bparser parser.tab.c parser.tab.h *~ \#*\#
