#include"headers/matrix.h"
#define ATTR_SET(flags, attr) (flags)|= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

struct matrix
{
	int maxx;
	int maxy;
	bool *state;
	bool evolution;
	uint32_t flags;
};

enum matrix_attr
{
	MATRIX_STATE
};

void static matrix_set_state(struct matrix *m, int i, int j, int z, bool state)
{
	if(i < m->maxx && j < m->maxy && i >= 0 && j >= 0)
		*(m->state + (z * m->maxx * m->maxy) + i * m->maxy + j) = state;
}



bool matrix_get_state(const struct matrix *m, int i , int j)
{
	int z = m->evolution;
	if(ATTR_IS_SET(m->flags, MATRIX_STATE))
		if(i < 0 || i >= m->maxx || j < 0 || j >= m->maxy)
			return false;
		else
			return *(m->state + (z * m->maxx * m->maxy) + i * m->maxy + j);
}

void liveOrDie(struct matrix *m, int i, int j, bool state)
{
	matrix_set_state(m,i,j,m->evolution,state);
}

void matrix_inicialize(struct matrix *m)
{
	int i,j;
	m->evolution=0;
	for(i = 0; i < m->maxx; i++){
		for (j = 0; j < m->maxy; j++)
			liveOrDie(m, i, j, false);
	}
	ATTR_SET(m->flags,MATRIX_STATE);
}

struct matrix *matrix_alloc(int x, int y)
{
	struct matrix *m;
	m = (struct matrix *) malloc(sizeof(struct matrix));
	if(m != NULL){
		m->flags = 0;
		m->maxx = x;
		m->maxy = y;
		m->state = (bool *) malloc( 2 * x * y * sizeof(bool));
	}
	return m;
}

void matrix_represent(const struct matrix *m)
{
	int i, j;
	int z = m->evolution;
	printf("\n\n");
	for (j = 0; j < (m->maxy); j++){
		for(i = 0; i < (m->maxx); i++){
			if(matrix_get_state(m,i,j))
				printf("[X]");
			else
				printf("[ ]");
		}
		printf("\n");
	}
}

//matrix_set_state(m,i,j,z,a > 1 && a < 4 );

static void darwin(int i, int j, struct matrix *m)
{
	int a = livingCellsAround(i, j, m);
	int z = (m->evolution);
	if(matrix_get_state(m,i,j))
		matrix_set_state(m, i, j, !z, a > 1 && a < 4 );
	else
		matrix_set_state(m, i, j, !z, a == 3);
}

void matrix_evolve(struct matrix *m)
{
	int i;
	int j;
	int a = m->evolution;
	for (j = 0; j < (m->maxy); j++){
		for(i = 0; i < (m->maxx); i++)
			darwin(i, j, m);
	}
	m->evolution = !m->evolution;
}

void matrix_free(struct matrix *m)
{
	free(m);
}

int livingCellsAround(int i, int j, const struct matrix *m)
{
	int a = 0;

	a += matrix_get_state(m,i,j-1);
	a += matrix_get_state(m,i-1,j);
	a += matrix_get_state(m,i-1,j-1);
	a += matrix_get_state(m,i,j+1);
	a += matrix_get_state(m,i+1,j);
	a += matrix_get_state(m,i+1,j+1);
	a += matrix_get_state(m,i-1,j+1);
	a += matrix_get_state(m,i+1,j-1);

	return a;
}
