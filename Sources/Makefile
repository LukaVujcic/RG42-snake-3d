PROGRAM = Snake3D.out
CC = gcc
LDLIBS  = -lglut -lGLU -lGL -lm
CFLAGS  = -g -std=c99 -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
$(PROGRAM): main.o drawing.o logic.o image.o map.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o drawing.o logic.o image.o map.o $(LDLIBS)
main.o: main.c
	$(CC) -c $(LDFLAGS) -o main.o main.c $(LDLIBS)
image.o: image.c
	$(CC) -c  -o image.o image.c 
drawing.o:  drawing.c
	$(CC) -c $(LDFLAGS) -o drawing.o drawing.c $(LDLIBS)
logic.o: logic.c
	$(CC) -c -o logic.o logic.c
map.o: map.c
	$(CC) -c -o map.o map.c
.PHONY: clean
clean:
	-rm *.o $(PROGRAM) 

