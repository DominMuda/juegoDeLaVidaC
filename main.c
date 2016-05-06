#include "headers/matrix.h"
#include <getopt.h>

void test1();
void test2();
void test3();

int main(int argc, char *argv[])
{
        int c,x,y,n;
        int option_index = 0;

        static struct option long_options[] =
        {
                {"X", required_argument, 0, 'x'},
                {"Y", required_argument, 0, 'y'},
                {"evo", required_argument, 0, 'n'},
                {0,0,0,0}
        };

        while ((c = getopt_long(argc, argv, "x:y:n:",long_options,&option_index)) != -1) {
                switch (c)
                        {
                        case'x':
                                x = strtol(optarg, NULL,0);
                                break;
                        case'y':
                                y = strtol(optarg, NULL,0);
                                break;
                        case'n':
                                n = strtol(optarg, NULL,0);
                                break;
                        case '?':
                                break;
                        default:
                                printf("ERROR\n");
                                break;
                }
        }
        //test1(x,y,n);
        //test2(x,y,n);
        test3(6,6,4);

        return EXIT_SUCCESS;
}

void test1(int x, int y,int n)
{
        int i, j, cont;
        struct matrix *m = matrix_alloc(x,y);
        matrix_inicialize(m);

        matrix_set_state(m, 4, 2, true);
        matrix_set_state(m, 3, 3, true);
        matrix_set_state(m, 5, 3, true);
        matrix_set_state(m, 5, 5, true);
        matrix_set_state(m, 3, 5, true);
        matrix_set_state(m, 4, 5, true);
        matrix_set_state(m, 5, 5, true);

        if(matrix_is_defined(m))
                for(cont = 0 ; cont < n; cont++){
                        matrix_represent(m);
                        matrix_evolve(m);
                }
        matrix_represent(m);
        matrix_free(m);
}

void test2(int x, int y,int n){
        int i, j, cont;
        struct matrix *m = matrix_alloc(x,y);
        matrix_inicialize(m);

        matrix_set_state(m, 6, 4, true);
        matrix_set_state(m, 6, 9, true);
        matrix_set_state(m, 6, 7, true);
        matrix_set_state(m, 6, 8, true);
        matrix_set_state(m, 5, 5, true);
        matrix_set_state(m, 7, 5, true);
        matrix_set_state(m, 4, 6, true);
        matrix_set_state(m, 8, 6, true);

        if(matrix_is_defined(m))
                for(cont = 0 ; cont < n; cont++){
                        matrix_represent(m);
                        matrix_evolve(m);
                }
        matrix_represent(m);
        matrix_free(m);
}

void test3(int x, int y,int n)
{
        int i, j, cont;
        struct matrix *m = matrix_alloc(x,y);
        matrix_inicialize(m);

        matrix_set_state(m, 0, 0, true);
        matrix_set_state(m, 0, 5, true);
        matrix_set_state(m, 1, 1, true);
        matrix_set_state(m, 1, 4, true);
        matrix_set_state(m, 2, 2, true);
        matrix_set_state(m, 2, 3, true);
        matrix_set_state(m, 3, 2, true);
        matrix_set_state(m, 3, 3, true);
        matrix_set_state(m, 4, 1, true);
        matrix_set_state(m, 4, 4, true);
        matrix_set_state(m, 5, 0, true);
        matrix_set_state(m, 5, 5, true);

        if(matrix_is_defined(m))
                for(cont = 0 ; cont < n; cont++){
                        matrix_represent(m);
                        matrix_evolve(m);
                }
        matrix_represent(m);
        matrix_free(m);
}
