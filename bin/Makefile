CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS =

all : test3.out unitest.out test2.out

unitest.out : graph.o $(SRC)unitest.c
	$(CC) $^ -g -o $@ $(LIBS)

test3.out : graph.o $(SRC)test3.c
	$(CC) $^ -g -o $@ $(LIBS)

test2.out : graph.o $(SRC)test2.c
	$(CC) $^ -g -o $@ $(LIBS)

test.out : ilist.o mgraph.o $(SRC)test.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
