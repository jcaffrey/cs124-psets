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
int** strassen(int** a, int** b, int cut, int n)
{
    int** c = newMatrix(n);

    if(n <= cut){
        conventional_multiply(c, a, b, n);  // TODO: DO I NEED TO BE RETURNING C for the recursion to work?
        //printMatrix(c, n);
        return c;
    }
    else
    {
        printf("got here!\n");

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

        p1 = strassen(A, s1, cut, nd);
        p2 = strassen(s2, H, cut, nd);
        p3 = strassen(s3, E, cut, nd);
        p4 = strassen(D, s4, cut, nd);
        p5 = strassen(s5, s6, cut, nd);
        p6 = strassen(s7, s8, cut, nd);
        p7 = strassen(s9, s10, cut, nd);

        int** c1 = newMatrix(nd);
        int** c2 = newMatrix(nd);
        int** c3 = newMatrix(nd);
        int** c4 = newMatrix(nd);
        int** t1 = newMatrix(nd);
        int** t2 = newMatrix(nd);
        int** t3 = newMatrix(nd);
        int** t4 = newMatrix(nd);

        // printf("\n p1 \n");
        // printMatrix(p1, nd);
        // printf("\n p2 \n");
        // printMatrix(p2, nd);
        // printf("\n p3 \n");
        // printMatrix(p3, nd);
        // printf("\n p4 \n");
        // printMatrix(p4, nd);
        // printf("\n p5 \n");
        // printMatrix(p5, nd);
        // printf("\n p6 \n");
        // printMatrix(p6, nd);
        // printf("\n p7 \n");
        // printMatrix(p7, nd);

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


        int i, j;
        for(i = 0; i < nd; i++)
        {
            for(j = 0; j < nd; j++)
            {
                c[i][j] = c1[i][j];
                c[i][j + nd] = c2[i][j];
                c[i + nd][j] = c3[i][j];
                c[i + nd][j + nd] = c4[i][j];
            }
        }

        return c;
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

        c = strassen(a, b, cut, n);


        printf("PRINTING C: \n");
        printMatrix(c, n);
    }

}
