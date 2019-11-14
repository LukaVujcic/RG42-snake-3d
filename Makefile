PROGRAM = Snake3D
CC = gcc
LDLIBS  = -lglut -lGLU -lGL -lm
CFLAGS  = -g -std=c99 -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
$(PROGRAM): main.o drawing.o logic.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o drawing.o logic.o $(LDLIBS)
main.o: main.c
	$(CC) -c $(LDFLAGS) -o main.o main.c $(LDLIBS)
drawing.o:  drawing.c
	$(CC) -c $(LDFLAGS) -o drawing.o drawing.c $(LDLIBS)
logic.o: logic.c
	$(CC) -c $(LDFLAGS) -o logic.o logic.c $(LDLIBS)
.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) 

