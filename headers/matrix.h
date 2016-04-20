#ifndef _MATRIX_H_
#define _MATRIX_H_

#define TAMX 3
#define TAMY 4

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct matrix{

	bool state[TAMX][TAMY];
	bool Nstate[TAMX][TAMY];
  int evolution;
};

void inicialize(struct matrix *m);
void represent(const struct matrix *m);
int livingCellsAround(int i, int j, const struct matrix *m);

struct matrix *matrix_alloc();

#endif
