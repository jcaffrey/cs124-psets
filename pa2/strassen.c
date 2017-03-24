#include <stdio.h>
#include <stdlib.h>


int** newMatrix(int sz) {
    // allocate a flat array of elements
    int** nm = (int**)malloc(sz * sizeof(*nm));
    int i;
    for(i = 0; i < sz; i++)
        nm[i] = malloc(sz * sizeof(**nm));


    int j;
    for (i = 0; i < sz; i++)
        for(j = 0; j < sz; j++)
            nm[i][j] = 0;

    return nm;
}

int** setIndices(int** src, int i_jump, int j_jump, int d)
{
    int** nm = newMatrix(d);
    int i, j;
    for(i = 0; i < d; i++)
        for(j = 0; j < d; j++)
            nm[i][j] = src[i + i_jump][j + j_jump];
    return nm;
}


void conventional_multiply(int** c, int** a, int** b, int sz) // fix this to index into the right places!
{
    int i, k, j;
    for(i = 0; i < sz; i++)
        for(j = 0; j < sz; j++)
            for(k = 0; k < sz; k++)
                c[i][j] += a[i][k] * b[k][j];  // need 2*sz here?
    return;
}
//
// void subtraction(matrix* s, matrix* a, matrix* b, int sz, int big_n)
// {
//     int i;
//     int j;
//     for(i = 0; i < sz; i++)
//         for(j = 0; j < sz; j++)
//             ELEMENT(s, i, j) = ELEMENT(a, i, j) - ELEMENT(b, i, j); //
//     return;
// }
//
void addMatrices(int** res, int** a, int** b, int sz)
{
    int i;
    int j;
    for(i = 0; i < sz; i++)
    {
        for(j = 0; j < sz; j++)
        {
            res[i][j] = a[i][j] + b[i][j]; // need to multiply sz of b, a by twice times the number of times strassens was claled?
        }
    }
    return;
}

void subMatrices(int** res, int** a, int** b, int sz)
{
    int i;
    int j;
    for(i = 0; i < sz; i++)
    {
        for(j = 0; j < sz; j++)
        {
            res[i][j] = a[i][j] - b[i][j]; // need to multiply sz of b, a by twice times the number of times strassens was claled?
        }
    }
    return;
}
//
void printMatrix(int** matrix, int sz)
{
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            printf("%d\n", matrix[i][j]);
}
//
//
void strassen(int** c, int** a, int** b, int cut, int n)
{
    if(n <= cut){
        conventional_multiply(c, a, b, n);  // TODO: DO I NEED TO BE RETURNING C for the recursion to work?
        return;
    }
    else
    {
        int nd = n / 2;
        int** A = setIndices(a, 0, 0, nd);
        int** B = setIndices(a, 0, nd, nd);
        int** C = setIndices(a, nd, 0, nd);
        int** D = setIndices(a, nd, nd, nd);

        int** E = setIndices(b, 0, 0, nd);
        int** F = setIndices(b, 0, nd, nd);
        int** G = setIndices(b, nd, 0, nd);
        int** H = setIndices(b, nd, nd, nd);


        int** s1 = newMatrix(nd);
        int** s2 = newMatrix(nd);
        int** s3 = newMatrix(nd);
        int** s4 = newMatrix(nd);
        int** s5 = newMatrix(nd);
        int** s6 = newMatrix(nd);
        int** s7 = newMatrix(nd);
        int** s8 = newMatrix(nd);
        int** s9 = newMatrix(nd);
        int** s10 = newMatrix(nd);

        subMatrices(s1, F, H, nd);
        addMatrices(s2, A, B, nd);
        addMatrices(s3, C, D, nd);
        subMatrices(s4, G, E, nd);
        addMatrices(s5, A, D, nd);
        addMatrices(s6, E, H, nd);
        subMatrices(s7, B, D, nd);
        addMatrices(s8, G, H, nd);
        subMatrices(s9, A, C, nd);
        addMatrices(s10, E, F, nd);

        int** p1 = newMatrix(nd);
        int** p2 = newMatrix(nd);
        int** p3 = newMatrix(nd);
        int** p4 = newMatrix(nd);
        int** p5 = newMatrix(nd);
        int** p6 = newMatrix(nd);
        int** p7 = newMatrix(nd);

        strassen(p1, A, s1, cut, nd);
        strassen(p2, s2, H, cut, nd);
        strassen(p3, s3, E, cut, nd);
        strassen(p4, D, s4, cut, nd);
        strassen(p5, s5, s6, cut, nd);
        strassen(p6, s7, s8, cut, nd);
        strassen(p7, s9, s10, cut, nd);

        int** c1 = newMatrix(nd);
        int** c2 = newMatrix(nd);
        int** c3 = newMatrix(nd);
        int** c4 = newMatrix(nd);
        int** t1 = newMatrix(nd);
        int** t2 = newMatrix(nd);
        int** t3 = newMatrix(nd);
        int** t4 = newMatrix(nd);

        //C1<--P5+P4−P2+P6
        addMatrices(t1, p5, p4, nd);
        subMatrices(t2, t1, p2, nd);
        addMatrices(c1, t2, p6, nd);

        // C2<--P1+P2
        addMatrices(c2, p1, p2, nd);

        // C3<--P4+P3
        addMatrices(c3, p4, p3, nd);

        // C4<--P1+P5−P3−P7
        addMatrices(t3, p1, p5, nd);
        subMatrices(t4, t3, p3, nd);
        subMatrices(c4, t4, p7, nd);

        printf("\n c1 \n");
        printMatrix(c1, nd);



//
//         subtraction(s1, b12, b22, n/2); // b11, b22 need to know that the elements array is actually n long
//         addition(s2, a11, a12, n/2);
//         addition(s3, a21, a22, n/2;
//         subtraction(s4, b21, b11, n/2);
//         addition(s5, a11, a22, n/2);
//         addition(s6, b11, b22, n/2);
//         subtraction(s7, a12, a22, n/2);
//         addition(s8, b21, b22, n/2);
//         subtraction(s9, a11, a21, n/2);
//         addition(s10, b11, b12, n/2);
// /*
//         printf("\n b12 - b22 = s1\n");//  THIS WORKS WHEN BIG_N IS IN SUBTRACT AND ADDITION
//
//         printf("\n b12 \n");
//         printHalfSizeMatrix(b12, n/2);
//         printf("\n b22 \n");
//         printHalfSizeMatrix(b22, n/2);
//
//         printf("\n s1 \n");
//         printMatrix(s1, n/2);
// */
//         //instatiate p matrices
//         int* p1 = newMatrix(n/2);
//         int* p2 = newMatrix(n/2);
//         int* p3 = newMatrix(n/2);
//         int* p4 = newMatrix(n/2);
//         int* p5 = newMatrix(n/2);
//         int* p6 = newMatrix(n/2);
//         int* p7 = newMatrix(n/2);
//
//         strassen(p1, a11, s1, cut, n/2);
//         strassen(p2, s2, b22, cut, n/2);
//         strassen(p3, s3, b11, cut, n/2);   // careful! order mattered here...
//         strassen(p4, a22, s4, cut, n/2);
//         strassen(p5, s5, s6, cut, n/2);
//         strassen(p6, s7, s8, cut, n/2);
//         strassen(p7, s9, s10, cut, n/2);
//
//         // make these newMatrices?
// /*        int* c11 = c;
//         int* c12 = c + (n / 2);
//         int* c21 = c + ((n * n) / (2));
//         int* c22 = c + ((n * n) / (2))+ (n / 2);
// */
//         int* c11 = newMatrix(n/2);
//         int* c12 = newMatrix(n/2);
//         int* c21 = newMatrix(n/2);
//         int* c22 = newMatrix(n/2);
//         //C11<--P5+P4−P2+P6
//         int* tmp1 = newMatrix(n/2);
//         int* tmp2 = newMatrix(n/2);
//         addition(tmp1, p5, p4, n/2);
//
//
//         printf("\np1\n");
//         printMatrix(p1, n/2);
//         //printHalfSizeMatrix(p1, n/2);
//         printf("\np2\n");
//         printMatrix(p2, n/2);
//
//         printf("\np3\n");
//         printMatrix(p3, n/2);
//
//         printf("\np4\n");
//         printMatrix(p4, n/2);
//
//         printf("\np5\n");
//         printMatrix(p5, n/2);
//
//         printf("\np6\n");
//         printMatrix(p6, n/2);
//
//         printf("\np7\n");
//         printMatrix(p7, n/2);
//
//
//         subtraction(tmp2, tmp1, p2, n/2);
//
//
//         addition(c11, tmp2, p6, n/2);
//
//         printf("\n ------c11------\n");
//         printHalfSizeMatrix(c11, n/2);
//
//         // C12<--P1+P2
//         addition(c12, p1, p2, n/2);
//
//         // C21<--P4+P3
//         addition(c21, p4, p3, n/2);
//
//         // C22<--P1+P5−P3−P7
//         int* tmp3 = newMatrix(n/2);
//         int* tmp4 = newMatrix(n/2);
//         addition(tmp3, p1, p5, n/2);
//         subtraction(tmp4, tmp3, p3, n/2);
//         subtraction(c22, tmp4, p7, n/2);
//
// /*        printMatrix(c11, n/2);
//         printMatrix(c12, n/2);
//         printMatrix(c21, n/2);
//         printMatrix(c22, n/2);
// */
//         // setMatrixElements(c, c11, 0, 0);
//         // setMatrixElements(c, c12, 0, n/2);
//         // setMatrixElements(c, c21, n/2, 0);
//         // setMatrixElements(c, c22, n/2, n/2);

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

        int** a = newMatrix(n);
        int** b = newMatrix(n);
        int** c = newMatrix(n);

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
                a[i][j] = val;
            }
            if(tot >= n * n && tot < 2 * n * n)
            {
                b[i][j] = val;
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

//         // test setIndices
//         int nD = n/2;
//         // int** A = setIndices(a, nD, 0);
//         // int** B = setIndices(a, nD, nD);
//         // int** C = setIndices(a, nD, (n * nD));
//         // int** D = setIndices(a, nD, (n * nD) + nD);
//         int** A = newMatrix(n/2);
//         int** B = newMatrix(n/2);
//         int** C = newMatrix(n/2);
//         int** D = newMatrix(n/2);
//
//         int** E = newMatrix(n/2);
//         int** F = newMatrix(n/2);
//         int** G = newMatrix(n/2);
//         int** H = newMatrix(n/2);
//
// // usage for C: setIndices(a, n/2, 0, n/2)
// // usage for D: setIndices(a, n/2, n/2, n/2)
//         for(i = 0; i < nD; i++)
//         {
//             for(j = 0; j < nD; j++)
//             {
//                 A[i][j] = a[i][j];
//                 B[i][j] = a[i][j + nD];
//                 C[i][j] = a[i + nD][j];
//                 D[i][j] = a[i + nD][j+ nD];
//
//                 E[i][j] = b[i][j];
//                 F[i][j] = b[i][j + nD];
//                 G[i][j] = b[i + nD][j];
//                 H[i][j] = b[i + nD][j + nD];
//             }
//         }
//
//
//         printf("\na\n");
//         printMatrix(a, n/2);
//
//         // printf("\nC\n");
//         // printMatrix(C, n/2);
//
//         int** axb = newMatrix(n);
//         conventional_multiply(axb, a, b, n);
//
//         printf("\nAxA\n");
//         printMatrix(axb, n);

        // printf("\nD\n");
        // printMatrix(D, n/2);

        strassen(c, a, b, cut, n);


        printf("PRINTING C: \n");
        printMatrix(c, n);
    }

}
