#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <getopt.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

#define CUT 32

// me(m, sz, i, j)
//    Return a pointer to matrix element `m[i][j]` -- the element
//    at row `i` and column `j`. The matrix is square with dimension
//    `sz`. Requires: `i < sz && j < sz`
static inline int* me(int* m, size_t sz, size_t i, size_t j) {
    return &m[i * sz + j];
}

// fast_matrix_multiply(c, sz, a, b)
//    `a`, `b`, and `c` are square matrices with dimension `sz`.
//    Computes the matrix product `a x b` and stores it in `c`.
void conventional_multiply(int* c, size_t sz, int* a, int* b) {
    // clear `c`
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            *me(c, sz, i, j) = 0;

    // compute product and update `c`
        // want to read left to right for both
    for (size_t i = 0; i < sz; ++i)     
        for (size_t k = 0; k < sz; ++k)
            for (size_t j = 0; j < sz; ++j)
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
}

int main(int argc, char* argv[]) {
    int d;
    // size_t sz = 1000;
    FILE *in;

    if(argc != 4) {
        printf("Proper usage: ./strassen [optional] [dimension] [inputfile]\n");
        return 1;
    }
    else 
    {
        in = fopen(argv[3], "r");
        d = atoi(argv[2]);

        // allocate matrices
        int* a = (int*) malloc(sizeof(int) * (size_t)d * (size_t)d);
        int* b = (int*) malloc(sizeof(int) * (size_t)d * (size_t)d);
        int* c = (int*) malloc(sizeof(int) * (size_t)d * (size_t)d);

        if(in == NULL) {
            printf("Error reading file\n");
            return 1;            
        }

        int i = 0;
        int j = 0;
        int tot = 0;
        int val;

        while(fscanf(in, "%d", &val) != EOF) 
        {
            if(i == j)
            {
                printf("%d\n", val);
            }
            if(tot < d * d) 
            {
                // add to matrix A
                *me(a, d, i, j) = val;
            }
            if(tot >= d*d && tot < 2 * d *d)
            {
                // add to matrix B
                *me(b, d, i, j) = val;

            }

            tot++;
            j++;
            if(j == d)
            {
                j = 0;
                i++;
            }
            if(tot == d * d)
                i = 0;
        }
        // print input matrices
/*
        // print matrices
        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", *me(a, (size_t)d, (size_t)i, (size_t)j));

        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", *me(b, (size_t)d, (size_t)i, (size_t)j));
*/
        // compute `c = a x b`
        conventional_multiply(c, (size_t)d, a, b);  // this is how to call..

        // print result matrix
/*        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", *me(c, (size_t)d, (size_t)i, (size_t)j));
*/        
        free(a);
        free(b);
        free(c);

    }



}
