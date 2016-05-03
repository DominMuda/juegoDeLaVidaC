#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

struct matrix;
struct state;

void inicialize(struct matrix *m);
void matrix_represent(const struct matrix *m);
int livingCellsAround(int i, int j, const struct matrix *m);
void matrix_evolve( struct matrix *m);

struct matrix *matrix_alloc();
struct state *state_alloc();

#endif
