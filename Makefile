target: parser

OBJS=func.o linkedlist.o verticeList.o faceList.o numList.o object.o
CFLAGS=-g -O3 -pedantic -Wall -Wextra -Werror

lex.yy.c: parser.l parser.tab.h
	flex parser.l

parser.tab.c parser.tab.h: parser.y func.h linkedlist.h object.h verticeList.h faceList.h numList.h
	bison -v -d parser.y

parser: lex.yy.c $(OBJS) 
	gcc $(CFLAGS) -Wno-unused-function -Wno-error=unused-function -o $@ parser.tab.c lex.yy.c $(OBJS) -lfl

func.o: func.c func.h
	gcc $(CFLAGS) -c func.c

linkedlist.o: linkedlist.c linkedlist.h
	gcc $(CFLAGS) -c linkedlist.c

verticeList.o: verticeList.c verticeList.h linkedlist.h
	gcc $(CFLAGS) -c verticeList.c

numList.o: numList.c numList.h linkedlist.h
	gcc $(CFLAGS) -c numList.c

faceList.o: faceList.c faceList.h linkedlist.h numList.h
	gcc $(CFLAGS) -c faceList.c

object.o: object.c object.h linkedlist.h
	gcc $(CFLAGS) -c object.c

clean:
	rm -rf parser lex.yy.c bparser parser.tab.c parser.tab.h *~ \#*\# *.o

