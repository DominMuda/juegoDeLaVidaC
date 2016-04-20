#include<stdio.h>
#include"headers/matrix.h"



void inicialize(struct matrix *matriz){
				free(matriz);
 				int i;
        int j;
				matriz->evolution=0;
        for (i = 0;i<TAMX;i++){
                for(j = 0;j<TAMY;j++){
                matriz->state[i][j]=false;
								matriz->Nstate[i][j]=false;
       		}
		 }
}
void represent(const struct matrix *matriz){
        int i;
        int j;
        for (i = 0;i<TAMY;i++){
                for(j = 0;j<TAMX;j++){
                			if(matriz->state[i][j] ){
											printf("[X]");
											}else {
											printf("[ ]");
											}
						}
						printf("\n");
      }
}

int livingCellsAround(int i, int j, const struct matrix *m){

	int a = 0;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;

	return a;
}

struct  matrix *matrix_alloc(){

	struct matrix *m;
	m = (struct matrix *)malloc(sizeof(struct matrix));

	return m;
}
/*si la cell viva sigue viviendo si tiene 2 o 3 cell vecinas vivas.
Si esta muerta, nace si tiene exactamente 3 cells vecinas vivas*/

int livingCellsAround(int i, int j, const struct matrix *m){

	int a = 0;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;
	a += m->state[i][j]==true;

	return a;
}


void darwin(int i, int j, const struct matrix *m){
		int a = livingCellsAround(i,j,m);
			if(m->state[i][j]){
				if(a==2||a==3){
				m->Nstate[i][j]==true;
				}
			}else{
				if(a==3){
				m->state[i][j]==true;
		}
	}
}

void evoluciona(const struct matrix *m){
		int i;
		int j;
		for (i = 0;i<TAMY;i++){
						for(j = 0;j<TAMX;j++){
						darwin(i,j,m)
				}
				printf("\n");
	}

}
