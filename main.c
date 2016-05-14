#include "headers/matrix.h"
#include "headers/list.h"
#include <getopt.h>

void test1();
void test2();
void test3();
void testList();

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
        //test3(x,y,n);
        testList();


        return EXIT_SUCCESS;
}

void test1(int x, int y,int n)
{
        int i, j, cont;
        struct matrix *m = matrix_alloc(x,y);

        if(m==NULL){
                perror("ERROR : ");
        }else{
                matrix_inicialize(m);

                liveOrDie(m, 4, 2, true);
                liveOrDie(m, 3, 3, true);
                liveOrDie(m, 5, 3, true);
                liveOrDie(m, 5, 5, true);
                liveOrDie(m, 3, 5, true);
                liveOrDie(m, 4, 5, true);
                liveOrDie(m, 5, 5, true);

                for(cont = 0 ; cont < n; cont++){
                        matrix_represent(m);
                        matrix_evolve(m);
                }
                matrix_represent(m);
                matrix_free(m);
        }
}

void test2(int x, int y,int n){
        int i, j, cont;
        struct matrix *m = matrix_alloc(x,y);

        if(m==NULL){
                perror("ERROR : ");
        }else{
                matrix_inicialize(m);

                liveOrDie(m, 6, 4, true);
                liveOrDie(m, 6, 9, true);
                liveOrDie(m, 6, 7, true);
                liveOrDie(m, 6, 8, true);
                liveOrDie(m, 5, 5, true);
                liveOrDie(m, 7, 5, true);
                liveOrDie(m, 8, 6, true);
                liveOrDie(m, 4, 6, true);

                for(cont = 0 ; cont < n; cont++){
                        matrix_represent(m);
                        matrix_evolve(m);
                }
                matrix_represent(m);
                matrix_free(m);
        }
}

void test3(int x, int y,int n)
{
        int i, j, cont;
        struct matrix *m = matrix_alloc(x,y);

        if(m==NULL){
                perror("ERROR : ");
        }else{
                matrix_inicialize(m);

                liveOrDie(m, 0, 0, true);
                liveOrDie(m, 0, 5, true);
                liveOrDie(m, 1, 1, true);
                liveOrDie(m, 2, 2, true);
                liveOrDie(m, 1, 4, true);
                liveOrDie(m, 2, 3, true);
                liveOrDie(m, 3, 2, true);
                liveOrDie(m, 3, 3, true);
                liveOrDie(m, 4, 1, true);
                liveOrDie(m, 4, 4, true);
                liveOrDie(m, 5, 5, true);
                liveOrDie(m, 5, 0, true);

                matrix_represent(m);

                for(cont = 0 ; cont < n; cont++){
                        afterLifeList(m);
                        liveOrDieList(m);
                        matrix_represent(m);
                }

                matrix_free(m);
        }
}

void testList(){
        int i, j, cont;
        struct matrix *m = matrix_alloc(7,7);
        if(m==NULL){
                perror("ERROR : ");
        }else{
                matrix_inicialize(m);

                liveOrDie(m, 3, 4, true);
                liveOrDie(m, 3, 2, true);
                liveOrDie(m, 3, 3, true);

                matrix_represent(m);

                for(cont = 0 ; cont < 4; cont++){
                        afterLifeList(m);
                        liveOrDieList(m);
                        matrix_represent(m);
                }

                matrix_free(m);
        }
}
