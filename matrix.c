#include "headers/matrix.h"
#include "headers/list.h"
#define ATTR_SET(flags, attr) (flags)|= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

struct matrix
{
	int maxx;
	int maxy;
	bool *state;
	bool evolution;
	struct list_head alive;
	struct list_head dead;
	struct list_head revive;
	uint32_t m_flags;
};

struct state
{
	int x;
	int y;
	struct list_head list;
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
	if(ATTR_IS_SET(m->m_flags, MATRIX_STATE))
		if(i < 0 || i >= m->maxx || j < 0 || j >= m->maxy)
			return false;
		else
			return *(m->state + (z * m->maxx * m->maxy) + i * m->maxy + j);
}

void matrix_inicialize(struct matrix *m)
{
	int i,j;
	m->evolution=0;
	for(i = 0; i < m->maxx; i++){
		for (j = 0; j < m->maxy; j++)
			liveOrDie(m, i, j, false);
	}
	ATTR_SET(m->m_flags, MATRIX_STATE);
}


struct matrix *matrix_alloc(int x, int y)
{
	struct matrix *m;
	m = (struct matrix *) malloc(sizeof(struct matrix));
	if(m != NULL){
		m->m_flags = 0;
		m->maxx = x;
		m->maxy = y;
		m->state = (bool *) malloc( 2 * x * y * sizeof(bool));
		INIT_LIST_HEAD(&m->alive);
		INIT_LIST_HEAD(&m->dead);
		INIT_LIST_HEAD(&m->revive);
	}
	return m;
}

struct state *state_alloc(int x, int y)
{
	struct state *st;
	st = (struct state *) malloc(sizeof(struct state));
	if(st!=NULL){
		st->y = y;
		st->x = x;
	}
	return st;
}


void liveOrDie(struct matrix *m, int i, int j, bool state)
{
	matrix_set_state(m,i,j,m->evolution,state);
	if(state){
		struct state *st = state_alloc(i,j);
		list_add(&st->list, &m->alive);
	}
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

void afterLifeList(struct matrix *m)
{
	int i,j,a;
	struct state *st;
	struct state *tmp;
	struct state *aux;
	list_for_each_entry_safe(st,tmp, &m->alive, list){
		a = livingCellsAround(st->x, st->y, m);
		if(a <= 1 || a >= 4 ){
			list_move(&(st->list), &m->dead);
		}
		for (i = -1; i <= 1;i++) {
			for(j = -1; j <= 1; j++){
				if (!matrix_get_state(m,(st->x) + i, (st->y) + j) && livingCellsAround((st->x) + i, (st->y) + j, m) == 3){
					aux = state_alloc(st->x + i, st->y + j);
					list_add(&aux->list, &m->revive);
				}
			}
		}
	}
}

void liveOrDieList(struct matrix *m)
{
	int i, j;
	struct state *st;
	struct state *tmp;
	struct state *tmp1;
	list_for_each_entry_safe(st,tmp, &m->dead, list){
		liveOrDie(m, st->x, st->y,false);
		list_del(&(st->list));
	}

	list_for_each_entry_safe(st,tmp, &m->revive, list){
		if(matrix_get_state(m, i, j)){
			list_del(&(st->list));
		}else{
			liveOrDie(m,st->x,st->y,true);
			list_move(&(st->list), &m->alive);
		}
	}
}
