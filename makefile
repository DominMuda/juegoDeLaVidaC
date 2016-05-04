.PHONY: clean
all: mi_proy

mi_proy:main.o
	gcc main.o matrix.o -o mi_proy

main.o:main.c
	gcc -c main.c

matrix.o: headers/matrix.h matrix.c
	gcc -c matrix.c

clean:
	rm -f *.o
	rm -f mi_proy

val: mi_proy
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./mi_proy
