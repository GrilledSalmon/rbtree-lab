#include <stdio.h>
#include <stdlib.h>

enum Rainbow{
    red=1,
    orage,
    yellow,
    green,
    blue,
    indigo,
    violet
};

void mal_test(double **p) {
    *p = (double *)malloc(0);
    // *p = (double *)calloc(1,0);
    free(*p);
    (*p)[0] = 3;
    (*p)[1] = 4;
    (*p)[2] = 5;
    // (*p)[1000] = 5;
    // p[1000] = 10;
    // for (int i=0;i<3;i++) {
    //     printf("%d \n", p[i]);
    //     printf("%p\n", &p[i]);
    // }
    // printf("%d\n", p[1000]);
    // printf("%p\n", &p[1000]);    
    // return p;
}

void main()
{

    // int *p = (void *)malloc(4);

    // p[0] = 3;
    // p[1] = 4;
    // p[2] = 5;
    
    double *p;
    mal_test(&p);
    
    for (int i=0;i<4;i++) {
        printf("%f \n", p[i]);
        printf("%p\n", &p[i]);
    }   
    // printf("%d\n", p[1000]);
    // printf("%p\n", &p[1000]);

    // return 0;
}

