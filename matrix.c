#include<stdio.h>
#include"headers/matrix.h"

#define TAMY 2
#define TAMX 1

void inicializa(char cells[TAMX][TAMY]){
	int i;
	int j;
	for (i = 0;i<TAMX;i++){
		for(j = 0;j<TAMY;j++){
		cells[i][j] = '%';
		printf("[%c]", cells[i][j]);
		}
		printf("\n");
	}
}


void representa(char cells[TAMX][TAMY]){
        int i;
        int j;
        for (i = 0;i<TAMX;i++){
                for(j = 0;j<TAMY;j++){
                printf("[%c]", cells[i][j]);
                }
                printf("\n");
        }
}



