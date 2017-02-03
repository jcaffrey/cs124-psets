#include <stdio.h>
#include <string.h>
// harvardID:10943485

#define SZ 2
#define FLOW 65536
unsigned int I[2][2];
int count = 0;

unsigned int fib(unsigned int n);
void matrixMultiply(unsigned int A[SZ][SZ], unsigned int B[SZ][SZ], unsigned int R[SZ][SZ]);
void matrixPower(unsigned int n);

int main(void)
{
    I[0][0] = 1;
    I[0][1] = 0;
    I[1][0] = 0;
    I[1][1] = 1;
    printf("%i\n", fib(10));
    printf("%i\n", count);
    return 1;
}

unsigned int fib(unsigned int n)
{
    matrixPower(n+1);
    return I[0][0];
}

void matrixMultiply(unsigned int A[SZ][SZ], unsigned int B[SZ][SZ], unsigned int R[SZ][SZ])
{
    count++;

    R[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0])%FLOW;
    R[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1])%FLOW;
    R[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0])%FLOW;
    R[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1])%FLOW;

    return;
}

void matrixPower(unsigned int n)
{
    unsigned int R[SZ][SZ];
    if (n > 1)
    {
        matrixPower(n / 2);
        matrixMultiply(I, I, R);
        memcpy(I, R, sizeof(R));
        //M = M*M;
    }
    unsigned int F[SZ][SZ];
    F[0][0] = 0;
    F[0][1] = 1;
    F[1][1] = 1;
    F[1][0] = 1;

    unsigned int A[2][2];
    if (n % 2 != 0)
    {
        matrixMultiply(I, F, A);
        memcpy(I, A, sizeof(A));
    }
    return;
}
