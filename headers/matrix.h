#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#define TAMX 9
#define TAMY 9

struct matrix;

void inicialize(struct matrix *m);
void represent(const struct matrix *m);
int livingCellsAround(int z,int i, int j, const struct matrix *m);
void darwin(int i, int j,  struct matrix *m);
void evolve( struct matrix *m);

struct matrix *matrix_alloc();

#endif
