#define _MATRIX_H_

#define TAMX 3
#define TAMY 4

struct matrix{
	int x;
	int y;
};

void inicialize (const struct matrix m, char cells[][]);
void represent (const struct matrix m, char cells[][]);

