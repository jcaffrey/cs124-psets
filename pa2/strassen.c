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

#define CUT 2 // only works with base case of 2 right now..

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


void conventional_multiply(matrix* c, int sz, matrix* a, matrix* b) // fix this to index into the right places!
{
    int i, k, j, a_k, b_k, c_i, a_i, c_j, b_j;
    for (i = 0, c_i = c->r_start, a_i = a->r_start; i < sz; i++, c_i++, a_i++)
        for (k = 0, a_k = a->c_start, b_k = b->r_start; k < sz; k++, a_k++, b_k++)
            for (j = 0, c_j = c->c_start, b_j = b->c_start; j < sz; j++, c_j++, b_j++)
                ELEMENT(c, c_i, c_j) += ELEMENT(a, a_i, a_k) * ELEMENT(b, b_k, b_j);

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

    for(i = 0, a_i = a->r_start, b_i = b->r_start; i < s->r_end; i++, a_i++, b_i++)
    {
        for(j = 0, a_j = a->c_start, b_j = b->c_start; j < s->c_end; j++, a_j++, b_j++)
        {
            ELEMENT(s, i, j) = ELEMENT(b, b_i, b_j) + ELEMENT(a, a_i, a_j); //             printf(" bi: %d,    bj: %d \n", b_i,  b_j);  // //i: %d,  ai: %d,  j: %d,   aj: %d,
        }
    }
    return;
}

void printMatrix(matrix* p)
{
    for(int i = p->r_start; i < p->r_end; i++)
    {
        for(int j = p->c_start; j < p->c_end; j++)
        {
            printf("%d\n", ELEMENT(p, i, j));
        }
    }
}

void setMatrixElements(matrix* c, matrix* a)
{
    int a_i, a_j, c_i, c_j;
    for(a_i = a->r_start, c_i = c->r_start; a_i < a->r_end; a_i++, c_i++)
        for(a_j = a->c_start, c_j= c->c_start; a_j < a->c_end; a_j++, c_j++)
            ELEMENT(c, c_i, c_j) = ELEMENT(a, a_i, a_j);
    return;
}

void strassen(matrix* c, int n, matrix* a, matrix*b)
{
    if(n <= CUT)
        conventional_multiply(c, n, a, b);  // TODO: DO I NEED TO BE RETURNING C for the recursion to work?
    else
    {
        // break a, b, c up using index calculations

        matrix* a11 = setIndices(a, 0, n/2, 0, n/2);
        matrix* a12 = setIndices(a, 0, n/2, n/2, n);
        matrix* a21 = setIndices(a, n/2, n, 0, n/2);
        matrix* a22 = setIndices(a, n/2, n, n/2, n);

        // printf("printing a!!!!!!\n");
        // printf("a11\n");
        // printMatrix(a11);
        // printf("a12\n");
        // printMatrix(a12);
        // printf("a21\n");
        // printMatrix(a21);
        // printf("a22\n");
        // printMatrix(a22);

        matrix* b11 = setIndices(b, 0, n/2, 0, n/2);
        matrix* b12 = setIndices(b, 0, n/2, n/2, n);
        matrix* b21 = setIndices(b, n/2, n, 0, n/2);
        matrix* b22 = setIndices(b, n/2, n, n/2, n);

        // printf("printing b!!!!!!\n");
        // printf("b11\n");
        // printMatrix(b11);
        // printf("b12\n");
        // printMatrix(b12);
        // printf("b21\n");
        // printMatrix(b21);
        // printf("b22\n");
        // printMatrix(b22);

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

        // printf("\nprinting!!!!!!\n");
        // printf("s1 = b12 - b22\n");
        // printMatrix(s1);
        // printf("\ns2 = a11+a12\n");
        // printMatrix(s2);
        // printf("\ns3 = a21 + a22\n");
        // printMatrix(s3);

        // printf("try to fix error with s4\n");
        // printf("b21\n");
        // printMatrix(b21);
        // printf("b11\n");
        // printMatrix(b11);

        //checking P1
        // printf("P1 = a11 * S1\n");
        // printf("\na11\n");
        // printMatrix(a11);
        // printf("\ns1\n");
        // printMatrix(s1);

        //checking P3
        // printf("P3 = b11 * S3\n");
        // printf("\nb11\n");
        // printMatrix(b11);
        // printf("\ns3\n");
        // printMatrix(s3);

        printf("P4 = a22 * S4\n");
        printf("\na22\n");
        printMatrix(a22);
        printf("\ns4\n");
        printMatrix(s4);


        // checking P5
        // printf("P5 = S5*S6\n");
        // printf("\ns5\n");
        // printMatrix(s5);
        // printf("\ns6\n");
        // printMatrix(s6);

        //

        //instatiate p matrices
        matrix* p1 = newMatrix(0, n/2, 0, n/2);
        matrix* p2 = newMatrix(0, n/2, 0, n/2);
        matrix* p3 = newMatrix(0, n/2, 0, n/2);
        matrix* p4 = newMatrix(0, n/2, 0, n/2);
        matrix* p5 = newMatrix(0, n/2, 0, n/2);
        matrix* p6 = newMatrix(0, n/2, 0, n/2);
        matrix* p7 = newMatrix(0, n/2, 0, n/2);

        // conventional_multiply(p3, n/2, b11, s3);
        // printf("conventional p3.......\n");
        // printMatrix(p3);

        strassen(p1, n/2, a11, s1);
        strassen(p2, n/2, b22, s2);
        strassen(p3, n/2, s3, b11);   // careful! order mattered here...
        strassen(p4, n/2, a22, s4);
        strassen(p5, n/2, s5, s6);
        strassen(p6, n/2, s7, s8);
        strassen(p7, n/2, s9, s10);

        // debugging c22
        // printf("\np1\n");
        // printMatrix(p1);
        // printf("\np5\n");
        // printMatrix(p5);
        // printf("\np3\n");
        // printMatrix(p3);
        // printf("\np7\n");
        // printMatrix(p7);
        // printf("\np4\n");
        // printMatrix(p4);


        // calculate the parts of c
        // matrix* c11 = setIndices(c, 0, n/2, 0, n/2);
        // matrix* c12 = setIndices(c, 0, n/2, n/2, n);
        // matrix* c21 = setIndices(c, n/2, n, 0, n/2);
        matrix* c11 = newMatrix(0, n/2, 0, n/2);
        matrix* c12 = newMatrix(0, n/2, 0, n/2);
        matrix* c21 = newMatrix(0, n/2, 0, n/2);
        matrix* c22 = newMatrix(0, n/2, 0, n/2);


        //C11←P5+P4−P2+P6
        matrix* tmp1 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp2 = newMatrix(0, n/2, 0, n/2);
        addition(tmp1, p5, p4);
        subtraction(tmp2, tmp1, p2);
        addition(c11, tmp2, p6);

        addition(c12, p1, p2);

        addition(c21, p4, p3);
        printf("\nc21 = p3+p4\n");
        printMatrix(c21);

        // C22←P1+P5−P3−P7
        matrix* tmp3 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp4 = newMatrix(0, n/2, 0, n/2);
        addition(tmp3, p1, p5); // p1 and p5 are correct...
        // printf("\ntmp3 = p1+p5\n");
        // printMatrix(tmp3);

        subtraction(tmp4, tmp3, p3);
        // printf("\ntmp4 = p1+p5-p3 = tmp3 -p3\n");
        // printMatrix(tmp4);


        subtraction(c22, tmp4, p7);
        // printf("\nc22 = p1+p5-p3-p7 = tmp4-p7\n");
        // printMatrix(c22);


        printf("\nPRINTING c11\n");
        printMatrix(c11);

        printf("\nPRINTING c12\n");
        printMatrix(c12);

        printf("\nPRINTING c21\n");
        printMatrix(c21);

        printf("\nPRINTING c22\n");
        printMatrix(c22);

        // copy all parts back into c and return
        setMatrixElements(c, c11);
        //setMatrixElements(c,  c12);
        setMatrixElements(c, c21);
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
