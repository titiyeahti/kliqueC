CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS =

all : test2.out

test2.out : graph.o $(SRC)test2.c
	$(CC) $^ -g -o $@ $(LIBS)

test.out : ilist.o mgraph.o $(SRC)test.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
