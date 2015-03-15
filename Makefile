target: parser

OBJS=func.o linkedlist.o verticeList.o object.o
CFLAGS=-g -pedantic -Wall -Wextra -Werror

lex.yy.c: parser.l parser.tab.h
	flex parser.l

parser.tab.c parser.tab.h: parser.y
	bison -v -d parser.y

parser: lex.yy.c $(OBJS)
	gcc $(CFLAGS) -Wno-error=unused-function -o $@ parser.tab.c lex.yy.c $(OBJS) -lfl

func.o: func.c func.h
	gcc $(CFLAGS) -c func.c

linkedlist.o: linkedlist.c linkedlist.h
	gcc $(CFLAGS) -c linkedlist.c

verticeList.o: verticeList.c verticeList.h linkedlist.h
	gcc $(CFLAGS) -c verticeList.c

object.o: object.c object.h linkedlist.h
	gcc $(CFLAGS) -c object.c

clear:
	rm -rf parser lex.yy.c bparser parser.tab.c parser.tab.h *~ \#*\#
