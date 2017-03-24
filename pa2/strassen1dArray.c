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

typedef struct {
    int r_start;
    int r_end;
    int c_start;
    int c_end;
    int isNew;
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

    // allocate a flat array of elements
    nm->elements = (int *) malloc(d * d * sizeof(int));

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
    nm->elements = (int *) malloc(sizeof(int)*(re - rs) * (ce - cs) * sizeof(int)); //size of this caused annoying error on addition step..s2..

    //nm->elements = m->elements;  // don't want to malloc here
/*    int m_i;
    int m_j;*/
    int i;
    int j;
    for(i = rs; i < re; i++)
        for(j = cs; j < ce; j++)
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
            //printf("i:%d,   j:%d\n", i, j);
            printf("%d\n", ELEMENT(p, i, j));
        }
    }
}

void setMatrixElements(matrix* c, matrix* a, int r_start, int c_start)
{
    int a_i, a_j, c_i, c_j;
    for(a_i = a->r_start, c_i = r_start; a_i < a->r_end; a_i++, c_i++){

        for(a_j = a->c_start, c_j= c_start; a_j < a->c_end; a_j++, c_j++){
            //printf("a_i: %d,   a_j:   %d,    c_i:    %d,     c_j:    %d\n", a_i,a_j,c_i,c_j);
            ELEMENT(c, c_i, c_j) = ELEMENT(a, a_i, a_j);
        }
    }
    return;
}

void strassen(matrix* c, int n, matrix* a, matrix*b, int cut)
{
    printf("calling strassen\n");
    if(n <= cut){
        conventional_multiply(c, n, a, b);  // TODO: DO I NEED TO BE RETURNING C for the recursion to work?
        return;
    }
    else
    {
        // break a, b, c up using index calculations
        matrix* a11 = setIndices(a, 0, n/2, 0, n/2);
        matrix* a12 = setIndices(a, 0, n/2, n/2, n);
        matrix* a21 = setIndices(a, n/2, n, 0, n/2);
        matrix* a22 = setIndices(a, n/2, n, n/2, n);

        matrix* b11 = setIndices(b, 0, n/2, 0, n/2);
        matrix* b12 = setIndices(b, 0, n/2, n/2, n);
        matrix* b21 = setIndices(b, n/2, n, 0, n/2);
        matrix* b22 = setIndices(b, n/2, n, n/2, n);

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

        //instatiate p matrices
        matrix* p1 = newMatrix(0, n/2, 0, n/2);
        matrix* p2 = newMatrix(0, n/2, 0, n/2);
        matrix* p3 = newMatrix(0, n/2, 0, n/2);
        matrix* p4 = newMatrix(0, n/2, 0, n/2);
        matrix* p5 = newMatrix(0, n/2, 0, n/2);
        matrix* p6 = newMatrix(0, n/2, 0, n/2);
        matrix* p7 = newMatrix(0, n/2, 0, n/2);

        strassen(p1, n/2, a11, s1, cut);
        strassen(p2, n/2, s2, b22, cut);
        strassen(p3, n/2, s3, b11, cut);   // careful! order mattered here...
        strassen(p4, n/2, a22, s4, cut);
        strassen(p5, n/2, s5, s6, cut);
        strassen(p6, n/2, s7, s8, cut);
        strassen(p7, n/2, s9, s10, cut);

        matrix* c11;
        matrix* c12;
        matrix* c21;
        matrix* c22;
        if(c->isNew == 1)
        {
            c11 = newMatrix(0, n/2, 0, n/2);  // is it bad to wipe these to 0 on recursion?
            c12 = newMatrix(0, n/2, 0, n/2);
            c21 = newMatrix(0, n/2, 0, n/2);
            c22 = newMatrix(0, n/2, 0, n/2);
            c->isNew = 0;
            //printf("\n newMatrix on c22\n");
        }
        else
        {
            printf("SETTING INDICES\n");
            c11 = setIndices(c, 0, n/2, 0, n/2);
            c12 = setIndices(c, 0, n/2, n/2, n);
            c21 = setIndices(c, n/2, n, 0, n/2);
            c22 = setIndices(c, n/2, n, n/2, n/2);
            /*printf("\nsetIndices on c22\n");
            printMatrix(c22);
*/
        }

        //C11<--P5+P4−P2+P6
        matrix* tmp1 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp2 = newMatrix(0, n/2, 0, n/2);
        addition(tmp1, p5, p4);
        subtraction(tmp2, tmp1, p2);
        addition(c11, tmp2, p6);

        // C12<--P1+P2
        addition(c12, p1, p2);

        // C21<--P4+P3
        addition(c21, p4, p3);

        // C22<--P1+P5−P3−P7
        matrix* tmp3 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp4 = newMatrix(0, n/2, 0, n/2);
        addition(tmp3, p1, p5);
        subtraction(tmp4, tmp3, p3);
        subtraction(c22, tmp4, p7);

        setMatrixElements(c, c11, 0, 0);
        setMatrixElements(c, c12, 0, n/2);
        setMatrixElements(c, c21, n/2, 0);
        setMatrixElements(c, c22, n/2, n/2);

        return;
    }
}



int main(int argc, char* argv[])
{
    int d;
    int cut;
    FILE* in;
    if(argc != 4) {
        printf("Proper usage: ./strassen [optional] [dimension] [inputfile]\n");
        return 1;
    }
    else
    {
        in = fopen(argv[3], "r");
        d = atoi(argv[2]);
        cut = atoi(argv[1]);

        matrix* a = newMatrix(0, d, 0, d);
        matrix* b = newMatrix(0, d, 0, d);
        matrix* c = newMatrix(0, d, 0, d);
        c->isNew = 1;

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
            // TODO; INCLUDE THIS IN THE FINAL
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

        strassen(c, d, a, b, cut);

        printf("PRINTING C: \n");
        printMatrix(c);
    }

}
