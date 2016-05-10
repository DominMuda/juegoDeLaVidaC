#include"headers/matrix.h"
#define ATTR_SET(flags, attr) (flags)|= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))
#define X 100
#define Y 100

struct matrix
{
	int maxx;
	int maxy;
	bool *state;
	bool evolution;
	uint32_t flags;
};

enum matrix_attr {
	MATRIX_STATE,
	MATRIX_EVO,
	MATRIX_MAXX,
	MATRIX_MAXY
};

void matrix_inicialize(struct matrix *m)
{
	int i,j;
	m->evolution=0;
	for(i = 0; i < m->maxx; i++){
		for (j = 0; j < m->maxy; j++)
			*(m->state + i * m->maxy + j) = false;
	}
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
			if(*(m->state + (z* m->maxx * m-> maxy) +i * m->maxy + j))
				printf("[X]");
			else
				printf("[ ]");
		}
		printf("\n");
	}
}

int checkCell(int i , int j, const struct matrix *m){
	int z = m->evolution;
	if(i < 0 || i >= m->maxx || j < 0 || j >= m->maxy)
		return false;
	else
		return *(m->state + (z* m->maxx * m->maxy) + i * m->maxy + j);
}

int livingCellsAround(int i, int j, const struct matrix *m)
{
	int a = 0;

	a += checkCell(i,j-1,m);
	a += checkCell(i-1,j,m);
	a += checkCell(i-1,j-1,m);
	a += checkCell(i,j+1,m);
	a += checkCell(i+1,j,m);
	a += checkCell(i+1,j+1,m);
	a += checkCell(i-1,j+1,m);
	a += checkCell(i+1,j-1,m);

	return a;
}

static void darwin(int i, int j, struct matrix *m)
{
	int a = livingCellsAround(i, j, m);
	int z = !(m->evolution);
	if(*(m->state + i * m->maxy + j) == true)
		*(m->state + (z* m->maxx * m->maxy) + i * m->maxy + j) = a > 1 && a < 4;
	else
		*(m->state + (z* m->maxx * m->maxy) + i * m->maxy + j) = a == 3;
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

void matrix_set_state(struct matrix *m,int i, int j, bool state)
{
	int z = m->evolution;
	if(i < m->maxx && j < m->maxy)
		*(m->state + (z* m->maxx * m->maxy) + i * m->maxy + j) = state;
	ATTR_SET(m->flags,MATRIX_STATE);
}

bool matrix_get_state(const struct matrix *m, int z, int i, int j)
{
	if(ATTR_IS_SET(m->flags, MATRIX_STATE))
		if(i < m->maxx && j < m->maxy)
			return *(m->state + (z* m->maxx * m->maxy) + i * m->maxy + j);
		else
			return NULL;
}

int matrix_get_maxx(const struct matrix *m)
{
	if(ATTR_IS_SET(m->flags, MATRIX_MAXX))
		return m->maxx;
	else
		return 0;
}

int matrix_get_maxy(const struct matrix *m)
{
	if(ATTR_IS_SET(m->flags, MATRIX_MAXY))
		return m->maxy;
	else
		return 0;
}
