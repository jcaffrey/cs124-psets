#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define B 1000000000
#define sz 20
#define trials 10

int main(void) {
    srand((unsigned) time(NULL));
    rand();

    int A[sz];

    int i, j, k, tot;
    double r;
    //double r_two;   // TASK 2 - uncomment this for task 2

    for(i = 0; i < trials; i++)
    {
        for(k=0; k < sz; k++)
            A[k] = 0;
        A[0] = B;
        for(j = 0; j < B; j++)
        {
            r = (double) rand() / (double) RAND_MAX;
            r = (int) (r * B);

            // TASK 2 - uncomment this for task 2
            // r_two = (double) rand() / (double) RAND_MAX;
            // r_two = (int) (r_two * B);

            if (r > r_two)
                r = r_two;

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

        // find index of max element
        for(k = 0; k < sz; k++)
        {
            if (A[k] == 0 && A[k + 1] == 0)
            {
                printf("%d\n", k-1);
                break;
            }
        }

    }

    return 0;
}
