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

typedef struct {
    int r_start;
    int r_end;
    int c_start;
    int c_end;
    int* elements;
} matrix;

#define ELEMENT(m, r, c) m->elements[(c-1) * m->r_end + (r-1)]

/*matrix conventional_multiply(matrix c, int sz, matrix a, matrix b)
{
    // clear `c`
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
            c.elements[i][j]
            *me(c, sz, i, j) = 0;

    // compute product and update `c`
        // want to read left to right for both
    for (size_t i = 0; i < sz; ++i)
        for (size_t k = 0; k < sz; ++k)
            for (size_t j = 0; j < sz; ++j)
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
}

void strassen(int* c, size_t n, int* a, int*b)
{
    if(n <= CUT)
        conventional_multiply(c, n, a, b);
    else
    {
        // break a, b, c up using index calculations
        int a11 = a
        return;
    }
}
*/
int main(int argc, char* argv[]) 
{
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
        matrix* a = (matrix*) malloc(sizeof(matrix));
        a->r_start = 0;
        a->r_end = d;
        a->c_start = 0;
        a->c_start = d;
        a->elements = (int*) malloc(sizeof(int) * d * d);

/*        matrix b;
        b.elements = malloc(sizeof(int) * d * d);
*/
        /*
        int* a = (int*) malloc(sizeof(int) * (size_t)d * (size_t)d);
        int* b = (int*) malloc(sizeof(int) * (size_t)d * (size_t)d);
        int* c = (int*) malloc(sizeof(int) * (size_t)d * (size_t)d);
*/
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
                ELEMENT(a, i, j) = val;
            }
/*            if(tot >= d*d && tot < 2 * d *d)
            {
                // add to matrix B
                b.elements[i][j] = val;

            }*/

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

        // print matrices
        int tmp =0;
        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
            {
                tmp = ELEMENT(a, i, j);
                printf("%d\n", tmp);
            }
                
/*        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", b.elements[i][j]);
*/
        // compute `c = a x b`
//        strassen(c, (size_t)d, a, b);  // this is how to call..

/*        // print result matrix
        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", *me(c, (size_t)d, (size_t)i, (size_t)j));
        
*/        free(a);
        //free(b);
       // free(c);

    }



}
