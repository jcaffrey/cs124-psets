#include <stdio.h>
#include <stdlib.h>

/*
0, 1, 2, 3,
4, 5, 6, 7,
8, 9, 0, 0,
0, 0, 0, 0,
*/
#define ELEMENT(m, i, j, big_n) m[i * big_n + j]  // this needs to be jump here instead

int* newMatrix(int sz) {
    // allocate a flat array of elements
    int* nm = (int *)malloc(sz * sz * sizeof(int));

    int i;
    for (i = 0; i < sz * sz; i++)
        nm[i] = 0.0;

    return nm;
}


void conventional_multiply(int* c, int* a, int* b, int sz) // fix this to index into the right places!
{
    int i, k, j;
    for(i = 0; i < sz; i++)
        for(j = 0; j < sz; j++)
            for(k = 0; k < sz; k++)
                ELEMENT(c, i, j, sz) += ELEMENT(a, i, k, sz) * ELEMENT(b, k, j, sz);  // need 2*sz here?
    return;
}

void subtraction(int* s, int* a, int* b, int sz)
{
    int i;
    int j;
    for(i = 0; i < sz; i++)
        for(j = 0; j < sz; j++)
            ELEMENT(s, i, j, sz) = ELEMENT(a, i, j, sz) - ELEMENT(b, i, j, sz); //
    return;
}

void addition(int* s, int* a, int* b, int sz)
{
    int i;
    int j;

    for(i = 0; i < sz; i++)
    {
        for(j = 0; j < sz; j++)
        {
            ELEMENT(s, i, j, sz) = ELEMENT(a, i, j, sz) + ELEMENT(b, i, j, sz); // need to multiply sz of b, a by twice times the number of times strassens was claled?
        }
    }
    return;
}

void printMatrix(int* matrix, int sz)
{
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            printf("%d\n", ELEMENT(matrix, i, j, sz));
}

/*void printHalfSizeMatrix(int* matrix, int sz, int big_n)
{
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            printf("%d\n", ELEMENT(matrix, i, j));
}
*/
/*void setMatrixElements(int* c, int* a, int r_start, int c_start)
{
    int a_i, a_j, c_i, c_j;
    for(a_i = a->r_start, c_i = r_start; a_i < a->r_end; a_i++, c_i++){

        for(a_j = a->c_start, c_j= c_start; a_j < a->c_end; a_j++, c_j++){
            //printf("a_i: %d,   a_j:   %d,    c_i:    %d,     c_j:    %d\n", a_i,a_j,c_i,c_j);
            ELEMENT(c, c_i, c_j) = ELEMENT(a, a_i, a_j);
        }
    }
    return;
}*/

void strassen(int* c, int* a, int*b, int cut, int n)
{
    if(n <= cut){
        conventional_multiply(c, a, b, n);  // TODO: DO I NEED TO BE RETURNING C for the recursion to work?
        return;
    }
    else
    {
        // break a, b, c up using index calculations
        int* a11 = a;
        int* a12 = a + (n / 2);
        int* a21 = a + ((n * n) / (2));
        int* a22 = a + ((n * n) / (2))+ (n / 2);

        int* b11 = b;
        int* b12 = b + (n / 2);
        int* b21 = b + ((n * n) / (2));
        int* b22 = b + ((n * n) / (2))+ (n / 2);

        int* s1 = newMatrix(n/2);
        int* s2 = newMatrix(n/2);
        int* s3 = newMatrix(n/2);
        int* s4 = newMatrix(n/2);
        int* s5 = newMatrix(n/2);
        int* s6 = newMatrix(n/2);
        int* s7 = newMatrix(n/2);
        int* s8 = newMatrix(n/2);
        int* s9 = newMatrix(n/2);
        int* s10 = newMatrix(n/2);

        subtraction(s1, b12, b22, n/2); // b11, b22 need to know that the elements array is actually n long
        addition(s2, a11, a12, n/2);
        addition(s3, a21, a22, n/2);
        subtraction(s4, b21, b11, n/2);
        addition(s5, a11, a22, n/2);
        addition(s6, b11, b22, n/2);
        subtraction(s7, a12, a22, n/2);
        addition(s8, b21, b22, n/2);
        subtraction(s9, a11, a21, n/2);
        addition(s10, b11, b12, n/2);

        //instatiate p matrices
        int* p1 = newMatrix(n/2);
        int* p2 = newMatrix(n/2);
        int* p3 = newMatrix(n/2);
        int* p4 = newMatrix(n/2);
        int* p5 = newMatrix(n/2);
        int* p6 = newMatrix(n/2);
        int* p7 = newMatrix(n/2);

        strassen(p1, a11, s1, cut, n/2);
        strassen(p2, s2, b22, cut, n/2);
        strassen(p3, s3, b11, cut, n/2);   // careful! order mattered here...
        strassen(p4, a22, s4, cut, n/2);
        strassen(p5, s5, s6, cut, n/2);
        strassen(p6, s7, s8, cut, n/2);
        strassen(p7, s9, s10, cut, n/2);

        // make these newMatrices?
/*        int* c11 = c;
        int* c12 = c + (n / 2);
        int* c21 = c + ((n * n) / (2));
        int* c22 = c + ((n * n) / (2))+ (n / 2);
*/
        int* c11 = newMatrix(n/2);
        int* c12 = newMatrix(n/2);
        int* c21 = newMatrix(n/2);
        int* c22 = newMatrix(n/2);
        //C11<--P5+P4−P2+P6
        int* tmp1 = newMatrix(n/2);
        int* tmp2 = newMatrix(n/2);
        addition(tmp1, p5, p4, n/2);
        printf("\n p5\n");
        printMatrix(p5, n/2);
        printf("\n p4\n");
        printMatrix(p4, n/2);
        printf("\n p2\n");
        printMatrix(p2, n/2);
        printf("\n p6\n");
        printMatrix(p6, n/2);


        printf("\n tmp1\n");
        printMatrix(tmp1, n/2);


        subtraction(tmp2, tmp1, p2, n/2);
        printf("\n tmp2\n");
        printMatrix(tmp2, n/2);


        addition(c11, tmp2, p6, n/2);

        printf("\n c11 = p5+p4-p2+p6.  tmp1 = p5+p4.  tmp2 = p5+p4-p2.  c11= tmp2+p6\n");
        printMatrix(c11, n/2);

        // C12<--P1+P2
        addition(c12, p1, p2, n/2);

        // C21<--P4+P3
        addition(c21, p4, p3, n/2);

        // C22<--P1+P5−P3−P7.   tmp3 = p1+p5, tmp4 = p1+p5-p3m   c22 = p1+p5-p3-p7
        int* tmp3 = newMatrix(n/2);
        int* tmp4 = newMatrix(n/2);
        addition(tmp3, p1, p5, n/2);
        subtraction(tmp4, tmp3, p3, n/2);
        subtraction(c22, tmp4, p7, n/2);

/*        printMatrix(c11, n/2);
        printMatrix(c12, n/2);
        printMatrix(c21, n/2);
        printMatrix(c22, n/2);
*/
        // setMatrixElements(c, c11, 0, 0);
        // setMatrixElements(c, c12, 0, n/2);
        // setMatrixElements(c, c21, n/2, 0);
        // setMatrixElements(c, c22, n/2, n/2);

        return;
    }
}

int main(int argc, char* argv[])
{
    int n;
    int cut;
    FILE* in;
    if(argc != 4) {
        printf("Proper usage: ./strassen [optional] [dimension] [inputfile]\n");
        return 1;
    }
    else
    {
        in = fopen(argv[3], "r");
        n = atoi(argv[2]);
        cut = atoi(argv[1]);

        int* a = newMatrix(n);
        int* b = newMatrix(n);
        int* c = newMatrix(n);

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
            if(tot < n * n)
            {
                ELEMENT(a, i, j, n) = val;
            }
            if(tot >= n * n && tot < 2 * n * n)
            {
                ELEMENT(b, i, j, n) = val;
            }
            tot++;
            j++;
            if(j == n)
            {
                j = 0;
                i++;
            }
            if(tot == n * n)
                i = 0;
        }

        strassen(c, a, b, cut, n);

        printf("PRINTING C: \n");
        printMatrix(c, n);
    }

}
