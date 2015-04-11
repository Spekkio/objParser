target: parser

OBJS=func.o linkedlist.o verticeList.o faceList.o numList.o object.o window.o simpleVerticeList.o
CFLAGS=-g -O3 -pedantic -Wall -Wextra -Werror -std=gnu99

lex.yy.c: parser.l parser.tab.h
	flex parser.l

parser.tab.c parser.tab.h: parser.y main.h func.h linkedlist.h object.h verticeList.h faceList.h numList.h window.h simpleVerticeList.h
	bison -v -d parser.y

parser: lex.yy.c $(OBJS)
	gcc $(CFLAGS) -Wno-unused-function -Wno-error=unused-function `pkg-config --cflags sdl gl glu glew` -o $@ parser.tab.c lex.yy.c $(OBJS) -lfl `pkg-config --libs sdl gl glu glew` -lm

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

window.o: window.c window.h main.h linkedlist.h
	gcc $(CFLAGS) `pkg-config --cflags sdl gl glu glew` -c window.c

simpleVerticeList.o: simpleVerticeList.c simpleVerticeList.h
	gcc $(CFLAGS) -c simpleVerticeList.c

clean:
	rm -rf parser lex.yy.c bparser parser.tab.c parser.tab.h *~ \#*\# *.o core

