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
    int i, j, k, tot;
    double r;
    for(k=0; k < sz; k++)
        A[k] = 0;

    for(i = 0; i < t; i++)
    {
        A[0] = B;
        for(j = 0; j < B; j++)
        {
            r = (double) rand() / (double) RAND_MAX;
            r = (int) (r * B);

            tot = 0;

            for (k = 0; k < sz; k++)
            {
                tot += A[k];
                if (r <= tot)
                {
                    A[k] -= 1;
                    A[k + 1] += 1;
                    break;
                }
            }

        }
        // print trial resutls here and reset..
    }

    for(k = 0; k < sz; k++)
        printf("%d\n", A[k]);

    // task 2: repeat above, but pick two bins and throw ball in least loaded of the two bins

    return 0;
}
