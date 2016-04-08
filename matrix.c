#include<stdio.h>
#include"matrix.h"
#include"cell.h"

void inicializa(const struct matrix m,cell cells[m.x][m.y]){
	int i;
	int j;
	for (i = 0;i<m.x;++){
		for(j = 0;j<m.y;j++){
		cells[i][j] = {'%'};
		printf("[%c]", cells[i][j].estado);
		}
		printf("\n");
	}
}


void representa(const struct matrix m,cell cells[m.x][m.y]){
        int i;
        int j;
        for (i = 0;i<m.x;++){
                for(j = 0;j<m.y;j++){
                printf("[%c]", cells[i][j].estado);
                }
                printf("\n");
        }
}


