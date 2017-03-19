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

#define CUT 2

typedef struct {
    int r_start;
    int r_end;
    int c_start;
    int c_end;
    int* elements;
} matrix;

#define ELEMENT(m, i, j) m->elements[i * (m->r_end - m->r_start) + j]  //test

matrix * newMatrix(int rs, int re, int cs, int ce) {
    int d;
    d = 0;
    if((re - rs) != (ce - cs)) {
        printf("Warning: instantiate square matrices only!\n");
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


void conventional_multiply(matrix* c, int sz, matrix* a, matrix* b)
{
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
    nm->elements = (int *) malloc((re - rs) * (re - rs) *(re - rs) * (ce - cs)  * sizeof(int)); //size of this caused annoying error on addition step..s2..

    //nm->elements = m->elements;  // don't want to malloc here
    for(int i = rs; i < re; i++)
        for(int j = cs; j < ce; j++)
            ELEMENT(nm, i, j) = ELEMENT(m, i, j);
    return nm;

}

void subtraction(matrix* s, matrix* a, matrix* b)
{
    int a_i;
    int a_j;
    int b_i;
    int b_j;
    int i;
    int j;
    for(i = 0, a_i = a->r_start, b_i = b->r_start; i < s->r_end; i++, a_i++, b_i++)
        for(j = 0, a_j = a->c_start, b_j = b->c_start; j < s->c_end; j++, a_j++, b_j++)
            ELEMENT(s, i, j) = ELEMENT(a, a_i, a_j) - ELEMENT(b, b_i, b_j); //             printf(" bi: %d,    bj: %d \n", b_i,  b_j);  // //i: %d,  ai: %d,  j: %d,   aj: %d,

    return;
}

void addition(matrix* s, matrix* a, matrix* b)
{
    int a_i;
    int a_j;
    int b_i;
    int b_j;
    int i;
    int j;
    // printf("s->rstart: %d a->rstart: %d, b->rstart: %d \n", s->r_start,a->r_start,b->r_start);
    // printf("s->rend: %d a->rend: %d, b->rend: %d \n", s->r_end,a->r_end,b->r_end);
    // printf("s->cend: %d a->cend: %d, b->cend: %d \n", s->c_end,a->c_end,b->c_end);
    printf("\nPRINTING COPY\n");

    for(i = 0, a_i = a->r_start, b_i = b->r_start; i < s->r_end; i++, a_i++, b_i++)
    {
        for(j = 0, a_j = a->c_start, b_j = b->c_start; j < s->c_end; j++, a_j++, b_j++)
        {
            ELEMENT(s, i, j) = ELEMENT(b, b_i, b_j) + ELEMENT(a, a_i, a_j); //             printf(" bi: %d,    bj: %d \n", b_i,  b_j);  // //i: %d,  ai: %d,  j: %d,   aj: %d,
        }
    }
    return;
}

void strassen(matrix* c, int n, matrix* a, matrix*b)
{

    if(n <= CUT)
        conventional_multiply(c, n, a, b);
    else
    {
        // break a, b, c up using index calculations

        // printf("\nPRINTING ORIG\n");
        // // for(int i = a11->r_start; i < a11->r_end; i++)
        // //     for(int j = a11->c_start; j < a11->c_end; j++)
        // //         printf("%d\n", ELEMENT(a11, i, j));
        //
        // for(int i = a12->r_start; i < a12->r_end; i++)
        // {
        //     for(int j = a12->c_start; j < a12->c_end; j++)
        //     {
        //         printf("bi: %d,   bj: %d \n", i, j);
        //
        //         printf("%d\n", ELEMENT(a12, i, j));
        //     }
        // }
        matrix* a11 = setIndices(a, 0, n/2, 0, n/2);
        matrix* a12 = setIndices(a, 0, n/2, n/2, n);
        matrix* a21 = setIndices(a, n/2, n, 0, n/2);
        matrix* a22 = setIndices(a, n/2, n, n/2, n);

        matrix* b11 = setIndices(a, 0, n/2, 0, n/2);
        matrix* b12 = setIndices(a, 0, n/2, n/2, n);
        matrix* b21 = setIndices(a, n/2, n, 0, n/2);
        matrix* b22 = setIndices(a, n/2, n, n/2, n);

        matrix* s1 = newMatrix(0, n/2, 0, n/2);
        matrix* s2 = newMatrix(0, n/2, 0, n/2);
        matrix* s3 = newMatrix(0, n/2, 0, n/2);
        matrix* s4 = newMatrix(0, n/2, 0, n/2);
        matrix* s5 = newMatrix(0, n/2, 0, n/2);
        matrix* s6 = newMatrix(0, n/2, 0, n/2);
        matrix* s7 = newMatrix(0, n/2, 0, n/2);
        matrix* s8 = newMatrix(0, n/2, 0, n/2);
        matrix* s9 = newMatrix(0, n/2, 0, n/2);
        matrix* s10 = newMatrix(0, n/2, 0, n/2);

        subtraction(s1, b12, b22);
        addition(s2, a11, a12);
        addition(s3, a21, a22);
        subtraction(s4, b21, b11);
        addition(s5, a11, a22);
        addition(s6, b11, b22);
        subtraction(s7, a12, a22);
        addition(s8, b21, b22);
        subtraction(s9, a11, a21);
        addition(s10, b11, b12);


        matrix* p1 = newMatrix(0, n/2, 0, n/2);
        matrix* p2 = newMatrix(0, n/2, 0, n/2);
        matrix* p3 = newMatrix(0, n/2, 0, n/2);
        matrix* p4 = newMatrix(0, n/2, 0, n/2);
        matrix* p5 = newMatrix(0, n/2, 0, n/2);
        matrix* p6 = newMatrix(0, n/2, 0, n/2);
        matrix* p7 = newMatrix(0, n/2, 0, n/2);

        strassen(p1, n/2, a11, s1);
        strassen(p2, n/2, s2, b22);
        strassen(p3, n/2, s3, b11);
        strassen(p4, n/2, a22, s4);
        strassen(p5, n/2, s5, s6);
        strassen(p6, n/2, s7, s8);
        strassen(p7, n/2, s9, s10);


        // calculate the parts of c
        matrix* c11 = setIndices(c, 0, n/2, 0, n/2);
        matrix* c12 = setIndices(c, 0, n/2, n/2, n);
        matrix* c21 = setIndices(c, n/2, n, 0, n/2);
        matrix* c22 = setIndices(c, n/2, n, n/2, n);


        //C11←P5+P4−P2+P6
        matrix* tmp1 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp2 = newMatrix(0, n/2, 0, n/2);
        addition(tmp1, p5, p4);
        subtraction(tmp2, tmp1, p2);
        addition(c11, tmp2, p6);

        addition(c12, p1, p2);

        addition(c21, p3, p4);

        // C22←P1+P5−P3−P7
        matrix* tmp3 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp4 = newMatrix(0, n/2, 0, n/2);
        addition(tmp1, p1, p5);
        subtraction(tmp2, tmp1, p3);
        subtraction(c22, tmp2, p7);


        printf("\nPRINTING c11\n");
        for(int i = c11->r_start; i < c11->r_end; i++)
            for(int j = c11->c_start; j < c11->c_end; j++)
                printf("%d\n", ELEMENT(c11, i, j));

        printf("\nPRINTING c12\n");
        for(int i = c12->r_start; i < c12->r_end; i++)
            for(int j = c12->c_start; j < c12->c_end; j++)
                printf("%d\n", ELEMENT(c12, i, j));

        printf("\nPRINTING c21\n");
        for(int i = c21->r_start; i < c21->r_end; i++)
            for(int j = c21->c_start; j < c21->c_end; j++)
                printf("%d\n", ELEMENT(c21, i, j));

        printf("\nPRINTING c22\n");
        for(int i = c22->r_start; i < c22->r_end; i++)
            for(int j = c22->c_start; j < c22->c_end; j++)
                printf("%d\n", ELEMENT(c22, i, j));
        //int a11 = a


        // copy all parts back into c and return
        return;
    }
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
        //strassen(c, d, a, b);
        strassen(c, d, a, b);

        printf("PRINTING C: \n");
        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", ELEMENT(c, i, j));
    }

}
