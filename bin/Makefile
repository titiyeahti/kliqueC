CC = gcc -Wall -Wextra -ansi -O2
SRC = ../src/
LIBS =

all : test3.out test2.out

test2.out : projet.o graph.o array.o ilist.o $(SRC)test2.c
	$(CC) $^ -g -o $@ $(LIBS)

test3.out : projet.o graph.o array.o ilist.o $(SRC)test3.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
