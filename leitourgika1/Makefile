# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g

OBJECTS = stack.o main.o graph.o

mygraph: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lm -o mygraph

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

clean:
	rm -fv mygraph