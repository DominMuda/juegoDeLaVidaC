#include"headers/matrix.h"

void test1();

int main(void){

        test1();

return EXIT_SUCCESS;
}

void test1(){
        int z;
        int i,j,cont;
        struct matrix *m = matrix_alloc();
        inicialize(m);
        z = matrix_get_evolution(m);

        //printf("\n%d\n",matrix_get_evolution(m));º
        matrix_set_state(m,z,4, 2, true);
        matrix_set_state(m,z,3, 3, true);
        matrix_set_state(m,z,5, 3, true);
        matrix_set_state(m,z,3, 5, true);
        matrix_set_state(m,z,4, 5, true);
        matrix_set_state(m,z,5, 5, true);


        for(cont =0;cont<15;cont++){
        represent(m);

        evolve(m);
}

        represent(m);


//        printf("\n%d\n",livingCellsAround(2,0,m));

//        evolve(m);

//        printf("\n%d\n",matrix_get_evolution(m));

//        represent(m);
}
