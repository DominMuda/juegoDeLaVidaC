#ifndef _MATRIX_H_
#define _MATRIX_H_
#include"cell.h"

struct matrix{
	int x;
	int y;
};

void inicialize (const struct matrix m, cell cells[][]);
void represent (const struct matrix m, cell cells[][]);

