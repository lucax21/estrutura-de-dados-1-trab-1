all: program

program: main.o matriz.o
	gcc main.o matriz.o -lm -o program

matriz.o: matriz.c matriz.h
	gcc -c matriz.c 

main.o: main.c matriz.h
	gcc -c main.c

clear:
	rm -rf *.o program
