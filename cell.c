#include<stdio.h>
#include"cell.h"

void kill_cell(struct cell *c){

	c->viva = '%';
}

void revive_cell(struct cell *c){

	c->estado =' ';
}
