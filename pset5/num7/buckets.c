#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define B 1000000000
#define sz 20
#define t 1

int main(void) {
    srand((unsigned) time(NULL));
    rand();
    int A[sz]; // A[i] indicatees number of bins with i balls, worst case -> 1 bin with B balls


    // task 1: throw 1B balls into 1B bins, 10 times
    int r, i, j, k, tot;
    for(k=0; k < sz; k++)
        A[k] = 0;

    for(i = 0; i < t; i++)
    {
        tot = 0;
        for(j = 0; j < B; j++)
        {
            r = (int) rand() % (int) B + 1;
            for (k = 0; k < sz; k++)
            {
                tot += A[k];
                if (r >= tot)
                {
                    break;
                }
            }
            A[k] = A[k] - 1;
            A[k + 1] = A[k + 1] + 1;
        }
    }

    for(k = 0; k < sz; k++)
        printf("%d\n", A[k]);

    // task 2: repeat above, but pick two bins and throw ball in least loaded of the two bins

    return 0;
}
