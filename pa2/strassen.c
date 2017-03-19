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

#define CUT 1

typedef struct {
    int r_start;
    int r_end;
    int c_start;
    int c_end;
    int* elements;
} matrix;

/*static inline int* me(int* ele, int sz, int i, int j) {
    return &ele[i * sz + j];
}*/
//#define ELEMENT(m, r, c) m->elements[(c) * m->r_end + (r)]

#define ELEMENT(m, i, j) m->elements[i + (m->r_end - m->r_start) * j]
//#define ELEMENT(m, i, j) m->elements[(m->r_end - m->r_start) * i + j]

void conventional_multiply(matrix* c, int sz, matrix* a, matrix* b)
{
    // clear `c`
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
            ELEMENT(c, i, j) = 0;

    // compute product and update `c`
        // want to read left to right for both
    for (int i = 0; i < sz; ++i)
        for (int k = 0; k < sz; ++k)
            for (int j = 0; j < sz; ++j)
                ELEMENT(c, i, j) += ELEMENT(a, i, k) * ELEMENT(b, k, j);
}

matrix* setIndices(matrix* m, int rs, int re, int cs, int ce)
{

    matrix * nm = (matrix *) malloc(sizeof(matrix));
    nm->r_start = rs;
    nm->r_end = re;
    nm->c_start = cs;
    nm->c_end = ce;
    // printf("ce - cs : %d\n",ce-cs );
    // printf("re - rs : %d\n",re-rs );
    nm->elements = (int *) malloc((re - rs)* (ce - cs)  * sizeof(int)); // needs to be multiplied by 4 for the lower matrices

    //nm->elements = m->elements;  // don't want to malloc here
    for(int i = rs; i < re; i++)
        for(int j = cs; j < ce; j++)
            ELEMENT(nm, i, j) = ELEMENT(m, i, j);
    return nm;

}


void strassen(matrix* c, int n, matrix* a, matrix*b)
{
    if(n <= CUT)
        conventional_multiply(c, n, a, b);
    else
    {
        // break a, b, c up using index calculations
        //matrix* a11 = setIndices(a, 0, n/2, 0, n/2);
        matrix* a12 = setIndices(a, 0, n/2, n/2, n);
        //matrix* a21 = setIndices(a, n/2, n, 0, n/2);
        //matrix* a22 = setIndices(a, n/2, n, n/2, n);

        for(int i = a12->r_start; i < a12->r_end; i++)
            for(int j = a12->c_start; j < a12->c_end; j++)
                printf("%d\n", ELEMENT(a12, i, j));
        //int a11 = a
        return;
    }
}



matrix * newMatrix(int rs, int re, int cs, int ce) {
    int d;
    d = 0;
    if((re - rs) != (ce - cs)) {
        printf("Warning: instatiate square matrices only!\n");
        return NULL;
    }
    else
    {
        d = re - rs;
    }

    matrix * nm = (matrix *) malloc(sizeof(matrix));

    // define indices
    nm->r_start = rs;
    nm->r_end = re;
    nm->c_start = cs;
    nm->c_end = ce;

    // allocate a double array of length rows * cols
    nm->elements = (int *) malloc(d * d * sizeof(int));
    // set all data to 0
    int i;
    for (i = 0; i < d * d; i++)
        nm->elements[i] = 0.0;

    return nm;
}

int main(int argc, char* argv[])
{
    int d;
    FILE* in;
    if(argc != 4) {
        printf("Proper usage: ./strassen [optional] [dimension] [inputfile]\n");
        return 1;
    }
    else
    {
        in = fopen(argv[3], "r");
        d = atoi(argv[2]);

        matrix* a = newMatrix(0, d, 0, d);
        matrix* b = newMatrix(0, d, 0, d);
        matrix* c = newMatrix(0, d, 0, d);

        if(in == NULL)
        {
            printf("Error reading file\n");
            return 1;
        }

        int i = 0;
        int j = 0;
        int tot = 0;
        int val;

        while(fscanf(in, "%d", &val) != EOF)
        {
            // if(i==j)
            //     printf("%d\n", val); // print diagonal entries
            if(tot < d * d)
            {
                //printf("adding %d at i : %d and j: %d\n", val, i , j);
                ELEMENT(a, i, j) = val;
            }
            if(tot >= d * d && tot < 2 * d *d)
            {
                ELEMENT(b, i, j) = val;
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
        strassen(c, d, a, b);
/*        for(i = 0; i < d; i++)
        {
            for(j = 0; j < d; j++)
            {
                printf("%d\n", ELEMENT(a, i, j));
            }
        }*/
    }

}
