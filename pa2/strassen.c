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

// me(m, sz, i, j)
//    Return a pointer to matrix element `m[i][j]` -- the element
//    at row `i` and column `j`. The matrix is square with dimension
//    `sz`. Requires: `i < sz && j < sz`
static inline double* me(double* m, size_t sz, size_t i, size_t j) {
    return &m[i * sz + j];
}

// fast_matrix_multiply(c, sz, a, b)
//    `a`, `b`, and `c` are square matrices with dimension `sz`.
//    Computes the matrix product `a x b` and stores it in `c`.
void fast_matrix_multiply(double* c, size_t sz, double* a, double* b) {
    // clear `c`
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            *me(c, sz, i, j) = 0;

    // compute product and update `c`
        // want to read left to right for both
    for (size_t j = 0; j < sz; ++j)     
        for (size_t k = 0; k < sz; ++k)
            for (size_t i = 0; i < sz; ++i)
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
}

// base_matrix_multiply(c, sz, a, b)
//    Same.
void base_matrix_multiply(double* c, size_t sz, double* a, double* b) {
    /*** DO NOT CHANGE THIS CODE!!!! ***/
    /* You should change fast_matrix_multiply. */
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            *me(c, sz, i, j) = 0;
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            for (size_t k = 0; k < sz; ++k)
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
}

// xrandom()
//    Return a pseudo-random number in the range [0, XRAND_MAX].
//    We use our own generator to ensure values computed on different
//    OSes will follow the same sequence.
#define XRAND_MAX 0x7FFFFFFF
static uint64_t xrandom_seed;
unsigned xrandom() {
    xrandom_seed = xrandom_seed * 6364136223846793005U + 1U;
    return (xrandom_seed >> 32) & XRAND_MAX;
}

typedef struct matrix_statistics {
    double corner[4];
    double diagonal_sum;
} matrix_statistics;

// compute_statistics(m, sz)
//    Compute and return some statistics about matrix `m`.
matrix_statistics compute_statistics(double* m, size_t sz) {
    matrix_statistics mstat;
    mstat.corner[0] = *me(m, sz, 0, 0);
    mstat.corner[1] = *me(m, sz, 0, sz-1);
    mstat.corner[2] = *me(m, sz, sz-1, 0);
    mstat.corner[3] = *me(m, sz, sz-1, sz-1);
    mstat.diagonal_sum = 0;
    for (size_t i = 0; i < sz; ++i)
        mstat.diagonal_sum += *me(m, sz, i, i);
    return mstat;
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
        printf("infile: %s\n", argv[3]);

        if(in == NULL) {
            printf("Error reading file\n");
            return 1;            
        }
        d = atoi(argv[2]);
        printf("DIM: %d\n", d);
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

            tot++;
            j++;
            if(j == d)
            {
                j = 0;
                i++;
            }
        }
    }
 /*   0
1
1
0
1
1
0
0
2
3
1
1
0
4
1
0
0
5*/
/*        int a = 1;
        int tot = 0;

        int diag_idx = 0;
        int val;
        int curr_line_idx = 0;
        int b = 1;
        // int count = 1;

        while(fscanf(in, "%d", &val) != EOF) 
        {
            if(tot == d * d)
                diag_idx = 0;
            if(tot < d * d - 1)
            {
                // add to matrix a
                a++;
            }
            if(tot > d * d && tot < 2 * d * d)
            {
                // add to matrix b
                b++;
            }
            if(curr_line_idx == diag_idx){              //&& tot%d == diag_idx){
                //printf("curr_line_idx: %d\n", curr_line_idx);
               // printf("diag_idx: %d\n", diag_idx);
                //// printf("TOT: %d\n", tot);
                printf("VAL: %d\n", val);
                //count++;
            }


            if(curr_line_idx == d-1) 
            {

                printf("curr_line_idx == d\n");
                curr_line_idx = 0;
                diag_idx++;
                //count = 1;
            }
            else
                curr_line_idx++;

            printf("tot: %d\n", tot);

            tot++;
        }
        printf("A: %d\n", a);
        printf("B: %d\n", b);

    }*/

    // FILE* in = fopen(infile, 'r')


/*
    assert(sz > 0);
    assert(sz < (size_t) sqrt(SIZE_MAX / sizeof(double)));

    // allocate matrices
    double* a = (double*) malloc(sizeof(double) * sz * sz);
    double* b = (double*) malloc(sizeof(double) * sz * sz);
    double* c = (double*) malloc(sizeof(double) * sz * sz);

    // fill in source matrices
    for (size_t i = 0; i < sz; ++i)
    for (size_t j = 0; j < sz; ++j)
        *me(a, sz, i, j) = xrandom() / (double) XRAND_MAX;

    for (size_t i = 0; i < sz; ++i)
    for (size_t j = 0; j < sz; ++j)
        *me(b, sz, i, j) = xrandom() / (double) XRAND_MAX;

    // compute `c = a x b`
    // fast_matrix_multiply(c, sz, a, b);  // this is how to call..


    free(a);
    free(b);
    free(c);*/
}
