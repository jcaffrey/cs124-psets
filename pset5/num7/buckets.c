#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define B 1000000000
#define sz 10000
#define t 10

int main(void) {
    srand((unsigned) time(NULL));
    rand();
    int A[sz]; // A[i] indicatees number of bins with i balls, worst case -> 1 bin with B balls

    // task 1: throw 1B balls into 1B bins, 10 times
    for(int i = 0; i < t; i++)
    {
        for(int j = 0; j < B; j++)
        {
            // throw 1B balls into 1B bins
        }
    }

    // task 2: repeat above, but pick two bins and throw ball in least loaded of the two bins

    double r =  (int)rand() % (int)B;
    printf("%f\n", r);
    printf("%d\n", B);
    return 0;
}
