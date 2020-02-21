CC = gcc -Wall -Wextra -ansi -O2
SRC = ../src/
LIBS =

all : test3.out

test2.out : projet.o graph.o array.o $(SRC)test2.c
	$(CC) $^ -g -o $@ $(LIBS)

test3.out : projet.o graph.o array.o ilist.o $(SRC)test3.c
	$(CC) $^ -g -o $@ $(LIBS)

test_graph.out : array.o graph.o $(SRC)test_graph.c
	$(CC) $^ -g -o $@ $(LIBS)

test_ilist.out : array.o ilist.o $(SRC)test_ilist.c
	$(CC) $^ -g -o $@ $(LIBS)

test_array.out : array.o $(SRC)test_array.c
	$(CC) $^ -g -o  $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
