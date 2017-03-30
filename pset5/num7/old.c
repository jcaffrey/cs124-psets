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
        for(j = 0; j < B; j++)
        {
            // calc rand # (1B times)
            r = (int)rand() % (int)B+1;
            tot = 0;
            k = 0;
            // find first index where number of balls
            while(r >= tot)
            {
                tot += A[k];
                k++;
                if (k >= sz - 1)
                {
                    //printf("Broke in bad way\n");
                    break;
                }
            }
            if (k > 2)
            {
                printf("%d\n", A[k]);
                /* code */
            }
            A[k] = A[k] - 1;
            A[k + 1] = A[k + 1] + 1;

/*            
            for(k = 0; k < sz; k++) // do this in a while?
            {
                tot += A[k];
                if(r >= tot)
                {
                    // decrement k'th bucket, increment k+1'th bucket
                    A[k] = A[k] - 1;
                    A[k + 1] = A[k + 1] + 1;
                    break;
                }
            }
*/        }
    }

    for(k = 0; k < sz; k++)
        printf("%d\n", A[k]);

    // task 2: repeat above, but pick two bins and throw ball in least loaded of the two bins

    return 0;
}
