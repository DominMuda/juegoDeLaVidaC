#include<stdio.h>

#include"headers/matrix.h"

int main(){

int i;
int j;
struct matrix m = {3,4};
char ma[m.x][m.y];

inicializa(m,ma);
return 0;
}
