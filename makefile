all: program

program: main.o matriz.o matriz_esparsa.o
	gcc main.o matriz.o matriz_esparsa.o -lm -o program

matriz.o: matriz.c matriz.h
	gcc -c matriz.c 

matriz_esparsa.o: matriz_esparsa.c matriz_esparsa.h
	gcc -c matriz_esparsa.c

main.o: main.c matriz.h
	gcc -c main.c

clean:
	rm -rf *.o main.o program
