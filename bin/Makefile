CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS =

all : test3.out

test2.out : projet.o graph.o array.o $(SRC)test2.c
	$(CC) $^ -g -o $@ $(LIBS)

test3.out : projet.o graph.o array.o $(SRC)test3.c
	$(CC) $^ -g -o $@ $(LIBS)

test_graph.out : array.o graph.o $(SRC)test_graph.c
	$(CC) $^ -g -o $@ $(LIBS)

test_array.out : array.o $(SRC)test_array.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
