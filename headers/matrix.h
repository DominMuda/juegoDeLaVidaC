#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

struct matrix;

void inicialize(struct matrix *m);
void matrix_represent(const struct matrix *m);
int livingCellsAround(int i, int j, const struct matrix *m);
void matrix_evolve( struct matrix *m);
bool matrix_is_defined(const struct matrix *m);

struct matrix *matrix_alloc();
void matrix_free(struct matrix *m);

#endif
