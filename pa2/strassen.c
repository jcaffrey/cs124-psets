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

#define CUT 1 // only works with base case of 2 right now..

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

/*        printf("P4 = a22 * S4\n");
        printf("\na22\n");
        printMatrix(a22);
        printf("\ns4\n");
        printMatrix(s4);
*/

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

        strassen(p1, n/2, a11, s1, cut);
        strassen(p2, n/2, b22, s2, cut);
        strassen(p3, n/2, s3, b11, cut);   // careful! order mattered here...
        strassen(p4, n/2, a22, s4, cut);
        strassen(p5, n/2, s5, s6, cut);
        strassen(p6, n/2, s7, s8, cut);
        strassen(p7, n/2, s9, s10, cut);

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

/*        matrix* c11 = newMatrix(0, n/2, 0, n/2);  // is it bad to wipe these to 0 on recursion?
        matrix* c12 = newMatrix(0, n/2, 0, n/2);
        matrix* c21 = newMatrix(0, n/2, 0, n/2);
        matrix* c22 = newMatrix(0, n/2, 0, n/2);
*/
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
        }
        else
        {
            c11 = setIndices(c, 0, n/2, 0, n/2);
            c12 = setIndices(c, 0, n/2, n/2, n);
            c21 = setIndices(c, n/2, n, 0, n/2);
            c22 = setIndices(c, n/2, n, n/2, n/2);
/*
            matrix* c11 = setIndices(c, 0, n/2, 0, n/2);
            matrix* c12 = setIndices(c, 0, n/2, 0, n/2);
            matrix* c21 = setIndices(c, 0, n/2, 0, n/2);
            matrix* c22 = setIndices(c, 0, n/2, 0, n/2);        // calculate the parts of c*/
        }


/*        printf("\np5\n");
        printMatrix(p5);
        printf("\np4\n");
        printMatrix(p4);
*/
        //C11←P5+P4−P2+P6
        matrix* tmp1 = newMatrix(0, n/2, 0, n/2);
        matrix* tmp2 = newMatrix(0, n/2, 0, n/2);
        addition(tmp1, p5, p4);

//        printf("\ntmp1\n");

        printMatrix(tmp1);
        subtraction(tmp2, tmp1, p2);
        addition(c11, tmp2, p6);
/*        printf("c11 = p5+p4-p2+p6\n");
        printMatrix(c11);
*/
        printf("\np1\n");
        printMatrix(p1);
        printf("\np2\n");
        printMatrix(p2);
/*        
        printf("p3\n");
        printMatrix(p3);
        printf("p4\n");
        printMatrix(p4); //degubbing for c12, c21
*/
        addition(c12, p1, p2);
        printf("\nc12 = p1+p2\n");
        //printf("c12->c_start: %d\n", c12->c_start);
        printMatrix(c12);

        addition(c21, p4, p3);
/*        printf("\nc21 = p3+p4\n");
        printMatrix(c21);
*/
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


/*        printf("\nPRINTING c11\n");
        printMatrix(c11);

        printf("\nPRINTING c12\n");
        printMatrix(c12);

        printf("\nPRINTING c21\n");
        printMatrix(c21);

        printf("\nPRINTING c22\n");
        printMatrix(c22);
*/

        // copy all parts back into c and return
    //    printf("N is: %d\n", n);
        setMatrixElements(c, c11, 0, 0);
        setMatrixElements(c, c12, 0, n/2);
        setMatrixElements(c, c21, n/2, 0);
        setMatrixElements(c, c22, n/2, n/2);

        //setMatrixElements(c, c22, n/2, n/2);
        //setMatrixElements(c,  c12);
       // setMatrixElements(c, c21);
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

        /*printMatrix(a);
        printf("PRINTING b: \n");

        printMatrix(b);
        *///strassen(c, d, a, b);
        strassen(c, d, a, b, cut);

        printf("PRINTING C: \n");
        printMatrix(c);
/*        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++)
                printf("%d\n", ELEMENT(c, i, j));
*/    }

}
