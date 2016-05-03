#include"headers/matrix.h"
#include"headers/list.h"
#define ATTR_SET(flags, attr) (flags)|= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))
#define X 100
#define Y 100

struct matrix
{
	int maxx;
	int maxy;
	bool state[2][X][Y];
	bool evolution;
	struct list_head head;
	uint32_t m_flags;
};

struct state
{
	struct matrix m;
	int x;
	int y;
	struct list_head list;
	uint32_t s_flags;
};

enum matrix_attr {
	MATRIX_STATE,
	MATRIX_MAXX,
	MATRIX_MAXY,
	MATRIX_HEAD
};

enum state_attr {
	STATE_X,
	STATE_Y,
};

void matrix_inicialize(struct matrix *m)
{
	int i,j;
	m->evolution=0;
	for (j = 0; j < m->maxy; j++){
		for(i = 0; i < m->maxx; i++)
		m->state[m->evolution][i][j] = false;
	}
}

struct  matrix *matrix_alloc(int x, int y)
{
	struct matrix *m;
	m = (struct matrix *) malloc( x * y * sizeof(struct matrix));
	m->m_flags = 0;
	m->maxx = x;
	m->maxy = y;
	return m;
}

struct  state *state_alloc(int x, int y, struct matrix *m)
{
	struct state *st;
	st = (struct state *) malloc(sizeof(struct state));
	st->m = *m;
	st->y = y;
	st->x = x;
	return st;
}

void matrix_represent(const struct matrix *m)
{
	int i, j;
	int z = m->evolution;
	printf("\n\n");
	for (j = 0; j < (m->maxy); j++){
		for(i = 0; i < (m->maxx); i++){
			if(m->state[z][i][j]){
				printf("[X]");
			}else{
				printf("[ ]");
			}
		}
		printf("\n");
	}
}

int checkCell(int i , int j, const struct matrix *m){
	if(i < 0 || i > m->maxx || j < 0 || j > m->maxy){
		return false;
	}else{
		return m->state[m->evolution][i][j];
	}
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
	int evo = m->evolution;
	int a = livingCellsAround(i, j, m);
	int z = !evo;
	if(m->state[evo][i][j] == true)
		m->state[z][i][j] = a > 1 && a < 4;
	else
		m->state[z][i][j] = a == 3;
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
	if(ATTR_IS_SET(m->m_flags, MATRIX_STATE))
		free(m->state);
	free(m);
}

void matrix_set_state(struct matrix *m,int i, int j, bool state)
{
	int z = m->evolution;
	if(ATTR_IS_SET(m->m_flags,MATRIX_STATE))
		free((int*)m->state[z][i][j]);
	if(i < m->maxx && j < m->maxy)
		m->state[z][i][j] = state;
	ATTR_SET(m->m_flags,MATRIX_STATE);
}

void matrix_set_maxX(struct matrix *m,int a)
{
	if(ATTR_IS_SET(m->m_flags,MATRIX_MAXX))
		free((int*)(m->maxx * sizeof(m->maxx)));
	m->maxx = a;
	ATTR_SET(m->m_flags,MATRIX_MAXX);
}

void matrix_set_maxY(struct matrix *m, int a)
{
	if(ATTR_IS_SET(m->m_flags,MATRIX_MAXY))
		free((int*)(m->maxy * sizeof(m->maxy)));
	m->maxy = a;
	ATTR_SET(m->m_flags,MATRIX_MAXY);
}

bool matrix_get_state(const struct matrix *m, int z, int i, int j)
{
	if(ATTR_IS_SET(m->m_flags, MATRIX_STATE))
		if(i < m->maxx && j < m->maxy)
			return m->state[z][i][j];
		else
			return NULL;
}

int matrix_get_maxx(const struct matrix *m)
{
	if(ATTR_IS_SET(m->m_flags, MATRIX_MAXX))
		return m->maxx;
	else
		return 0;
}

int matrix_get_maxy(const struct matrix *m)
{
	if(ATTR_IS_SET(m->m_flags, MATRIX_MAXY))
		return m->maxy;
	else
		return 0;
}

int state_get_y(const struct state *st)
{
	if(ATTR_IS_SET(st->s_flags, STATE_Y))
		if(st->x < st->m.maxx && st->y < st->m.maxy)
			return st->y;
		else
			return 0;
}

int state_get_x(const struct state *st)
{
	if(ATTR_IS_SET(st->s_flags, STATE_X))
		if(st->x < st->m.maxx && st->y < st->m.maxy)
			return st->y;
		else
			return 0;
}

void stateListAdd(struct list_head *list,  struct state *st,  struct matrix *m)
{
	if(!ATTR_IS_SET(m->m_flags, MATRIX_HEAD)){
		INIT_LIST_HEAD(list);
		list_add(&(m->head), list);
		ATTR_SET(m->m_flags,MATRIX_HEAD);
	}else{
		list_add(&(st->list),list);
	}
}

void aliveCellsList(struct list_head *alive, struct matrix *m)
{
	int i,j,z;
	z= m->evolution;
	for(i = 0;i<m->maxx;i++){
		for(j = 0; j< m->maxy;j++){
			if(m->state[z][i][j]){
			 struct state *st = state_alloc(i,j,m);
			 stateListAdd(alive, st, m);
			}
		}
	}
}

void getCellsList(struct list_head *alive, struct list_head *dead, struct list_head *revive, struct matrix *m)
{
	int i,j,a;

	struct state *st;
	struct state *aux;
	list_for_each_entry_safe(st, alive,list){
		a = livingCellsAround(st->x,st->y,m);
		if(a<1 || a>4 ){
			aux = state_alloc(st->x,st->y,m);
			list_del(&(st->list));
			free(st);
			stateListAdd(dead,aux,m);
		}
		for (i = -1; i <= 1;i++) {
			for(j = -1 ; j <= 1; j++){
				if (livingCellsAround(st->x + i,st->y + j,m)==3){
					aux = state_alloc(st->x+i,st->y+j,m);
					stateListAdd(revive,aux,m);
				}
			}
		}
	}
}
