PROGRAM = Snake3D
CC = gcc
LDLIBS  = -lglut -lGLU -lGL
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
$(PROGRAM): main.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o $(LDLIBS)
.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) 

