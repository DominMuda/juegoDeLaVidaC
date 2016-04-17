all: mi_proy

mi_proy:main.o matrix.o
	gcc main.o matrix.o -o mi_proy

main.o:main.c matrix.o
	gcc -c main.c

matrix.o: headers/matrix.h matrix.c
	gcc -c matrix.c
