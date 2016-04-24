#include"headers/matrix.h"
#define ATTR_SET(flags, attr) (flags)|= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))


struct matrix {
	bool state[2][TAMX][TAMY];
	bool evolution;
	uint32_t flags;

};

enum matrix_attr {
	MATRIX_STATE,
	MATRIX_EVO
};

void inicialize(struct matrix *matriz){
	int i;
	int j;
	matriz->evolution=0;
	for (j = 0;j<TAMY;j++){
		for(i = 0;i<TAMX;i++){
			matriz->state[matriz->evolution][i][j]=false;
		}
	}
}
void represent(const struct matrix *m){
	int i;
	int j;
	int z=m->evolution;
	printf("\n\n");
	for (j = 0;j<TAMY;j++){
		for(i = 0;i<TAMX;i++){
			if(m->state[z][i][j]){
				printf("[X]");
			}else {
				printf("[ ]");
			}
		}
		printf("\n");
	}
}

int returnLimits(int a, const struct matrix *m){
	if(a ==TAMX-1 || a==TAMY-1){
		return a-1;
	}else if(a==0){
		return a+1;
	}
}



int livingCellsAround(int z,int i, int j, const struct matrix *m){
	int a = 0;
	int j1=returnLimits(j,m);
	int i1=returnLimits(i,m);
	if(i==TAMX-1 || i==0){
		a += m->state[z][i][j-1];
		a += m->state[z][i1][j];
		a += m->state[z][i1][j-1];
		a += m->state[z][i][j+1];
		a += m->state[z][i1][j+1];
	}else if(j==TAMY-1||j==0){
		a += m->state[z][i-1][j];
		a += m->state[z][i+1][j];
		a += m->state[z][i][j1];
		a += m->state[z][i+1][j1];
		a += m->state[z][i-1][j1];
	}else{
		a += m->state[z][i][j-1];
		a += m->state[z][i-1][j];
		a += m->state[z][i-1][j-1];
		a += m->state[z][i][j+1];
		a += m->state[z][i+1][j];
		a += m->state[z][i+1][j+1];
		a += m->state[z][i-1][j+1];
		a += m->state[z][i+1][j-1];
	}
	return a;
}

/*si la cell viva sigue viviendo si tiene 2 o 3 cell vecinas vivas.
Si esta muerta, nace si tiene exactamente 3 cells vecinas vivas*/



void darwin(int i, int j, struct matrix *m){
	int evo = m->evolution;
	int a = livingCellsAround(evo,i,j,m);
	int z = (evo +1)%2;
	if(m->state[evo][i][j]==true){
		if(a<=1||a>=4){
			m->state[z][i][j]=false;
		}else{
			m->state[z][i][j]=true;
		}
	}else{
		if(a==3){
			m->state[z][i][j]=true;
		}else{
			m->state[z][i][j]=false;
		}
	}

}

void evolve(struct matrix *m){
	int i;
	int j;
	int a = m->evolution;
	for (j = 0;j<TAMY;j++){
		for(i = 0;i<TAMX;i++){
			darwin(i,j,m);
		}
	}
		m->evolution=(a+1)%2;
	}


struct  matrix *matrix_alloc(){
	struct matrix *m;
	m = (struct matrix *)malloc(TAMX*TAMY*sizeof(struct matrix));
	m->flags=0;
	return m;
}

void matrix_free(struct matrix *m){
	if(ATTR_IS_SET(m->flags,MATRIX_STATE))
	free(m->state);
	if(ATTR_IS_SET(m->flags,MATRIX_EVO))
	free((int*)m->evolution);
	free(m);
}


void matrix_set_state(struct matrix *m,int z,int i, int j, bool state){
	if(ATTR_IS_SET(m->flags,MATRIX_STATE))
	free((int*)m->state[z][i][j]);
	m->state[z][i][j]=state;
	ATTR_SET(m->flags,MATRIX_STATE);
}

void matrix_set_evolution(struct matrix *m, bool evo){
	if(ATTR_IS_SET(m->flags,MATRIX_EVO))
	free((int*)m->evolution);
	m->evolution=evo;
	ATTR_SET(m->flags,MATRIX_EVO);
}

bool matrix_get_state(const struct matrix *m, int z, int i, int j){
	if(ATTR_IS_SET(m->flags, MATRIX_STATE))
	return m->state[z][i][j];
	else
	return NULL;
}

bool matrix_get_evolution(const struct matrix *m){
	if(ATTR_IS_SET(m->flags, MATRIX_EVO))
	return m->evolution;
	else
	return NULL;
}
