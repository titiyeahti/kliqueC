CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS =

all : test.out

test.out : ilist.o mgraph.o $(SRC)test.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
