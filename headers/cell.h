#ifndef _CELL_H_
#define _CELL_H_

struct cell{
	char estado;
};

void kill_cell(struct cell *c);
void revive_cell(struct cell *c);

