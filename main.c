#include"headers/matrix.h"

void test1();
void test2();
void test3();

int main(int argc, char *argv[]){
        int c,x,y,n;
        while((c=getopt(argc, argv, "x:y:n:e:"))!=-1){
                switch(c){
                case'x':
                //tamaño en el eje X
                x = strtol(optarg, NULL,0);
                break;
                case'y':
                //tamaño en el eje Y
                y = strtol(optarg, NULL,0);
                break;
                case'n':
                //numero de test
                n = strtol(optarg, NULL,0);
                break;
                }
        }
        
        //test1(x,y,n);
        //test2(x,y,n);
        test3(x,y,n);

return EXIT_SUCCESS;
}

void test1(int x, int y,int n){
        int z;
        int i,j,cont;
        struct matrix *m = matrix_alloc(x,y);
        inicialize(m);
        z = matrix_get_evolution(m);

        //printf("\n%d\n",matrix_get_evolution(m));º
        matrix_set_state(m,z,4, 2, true);
        matrix_set_state(m,z,3, 3, true);
        matrix_set_state(m,z,5, 3, true);
        matrix_set_state(m,z,3, 5, true);
        matrix_set_state(m,z,4, 5, true);
        matrix_set_state(m,z,5, 5, true);


        for(cont =0;cont<n;cont++){
        represent(m);

        evolve(m);
}
        represent(m);
}

void test2(int x, int y,int n){
        int z;
        int i,j,cont;
        struct matrix *m = matrix_alloc(x,y);
        inicialize(m);
        z = matrix_get_evolution(m);

        //printf("\n%d\n",matrix_get_evolution(m));º

        matrix_set_state(m,z,6, 4, true);
        matrix_set_state(m,z,6, 9, true);
        matrix_set_state(m,z,6, 7, true);
        matrix_set_state(m,z,6, 8, true);

        matrix_set_state(m,z,5, 5, true);
        matrix_set_state(m,z,7, 5, true);
        matrix_set_state(m,z,4, 6, true);

        matrix_set_state(m,z,8, 6, true);


        for(cont =0;cont<n;cont++){
        represent(m);

        evolve(m);
}
        represent(m);
}

void test3(int x, int y,int n){
        int z;
        int i,j,cont;
        struct matrix *m = matrix_alloc(x,y);
        inicialize(m);
        z = matrix_get_evolution(m);

        //printf("\n%d\n",matrix_get_evolution(m));º

        matrix_set_state(m,z,0, 0, true);
        matrix_set_state(m,z,0, 5, true);
        matrix_set_state(m,z,1, 1, true);
        matrix_set_state(m,z,1, 4, true);

        matrix_set_state(m,z,2, 2, true);
        matrix_set_state(m,z,2, 3, true);
        matrix_set_state(m,z,3, 2, true);
        matrix_set_state(m,z,3, 3, true);

        matrix_set_state(m,z,4, 1, true);
        matrix_set_state(m,z,4, 4, true);
        matrix_set_state(m,z,5, 0, true);
        matrix_set_state(m,z,5, 5, true);


        for(cont =0;cont<n;cont++){
        represent(m);

        evolve(m);
}
        represent(m);
}
