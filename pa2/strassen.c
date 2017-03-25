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

int** padPow2Matrix(int** orig, int old_n, int n)
{
    int i, j;
    int** pm = newMatrix(n);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i >= old_n || j >= old_n)
            {
                //printf("padding matrix of sz: %d at i: %d and j: %d\n", sz, i, j);
                pm[i][j] = 0;
            }
            else
                pm[i][j] = orig[i][j];
        }
    }
    return pm;
}

// pad a row and col of zeroes if isOdd
int** setIndices(int** src, int i_jump, int j_jump, int d)
{
    int** nm = newMatrix(d);
    int i, j;

    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            nm[i][j] = src[i + i_jump][j + j_jump];
        }
    }
    return nm;
}


void conventional_multiply(int** c, int** a, int** b, int sz) // fix this to index into the right places!
{
    int i, k, j;
    for(i = 0; i < sz; i++)
        for(k = 0; k < sz; k++)
            for(j = 0; j < sz; j++)
                c[i][j] += a[i][k] * b[k][j];  // need 2*sz here?
    return;
}

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

void printMatrix(int** matrix, int sz)
{
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            printf("%d\n", matrix[i][j]);
}

int** strassen(int** a, int** b, int cut, int n)
{
    int** c = newMatrix(n);

    if(n <= cut) {// || n == 1){
        conventional_multiply(c, a, b, n);
        return c;
    }
    else
    {
        // TODO adjust a, b if odd

        int nd = n/2;
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

        // C1 = P5+P4−P2+P6
        addMatrices(t1, p5, p4, nd);
        subMatrices(t2, t1, p2, nd);
        addMatrices(c1, t2, p6, nd);

        // C2 = P1+P2
        addMatrices(c2, p1, p2, nd);

        // C3 = P4+P3
        addMatrices(c3, p4, p3, nd);

        // C4 = P1+P5−P3−P7
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
        free(p1);
        free(p2);
        free(p3);
        free(p4);
        free(p5);
        free(p6);
        free(p7);

        free(t1);
        free(t2);
        free(t3);
        free(t4);

        free(A);
        free(B);
        free(C);
        free(D);
        free(E);
        free(F);
        free(G);
        free(H);

        free(s1);
        free(s2);
        free(s3);
        free(s4);
        free(s5);
        free(s6);
        free(s7);
        free(s8);
        free(s9);
        free(s10);

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

        if(in == NULL)
        {
            printf("Error reading file\n");
            return 1;
        }

        int i = 0;
        int j = 0;
        int tot = 0;
        int val;

        // read in matrices according to spec - requires correct dimension
        while(fscanf(in, "%d", &val) != EOF)
        {
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

        int old_n = n;

        // calculate the new n (next highest power of 2) - http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
        unsigned int v;
        v = n;
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        n = v;

        a = padPow2Matrix(a, old_n, n);
        b = padPow2Matrix(b, old_n, n);

        int** c = newMatrix(n);

        c = strassen(a, b, cut, n);

        // print diagonal matrices of size old_n - TODO test
        n = old_n;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if(i == j)
                    printf("%d\n", c[i][j]);
            }
        }

    }
}
