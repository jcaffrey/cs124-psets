#include <stdio.h>
// harvardID:10943485

#define FLOW 65536

unsigned int fib(unsigned int n);

int main(void)
{
	printf("%d\n", fib(46));
	return 1;
}

unsigned int fib(unsigned int n) {
	unsigned int prevPrev = 0;
	unsigned int prev = 1;
	unsigned int curr;
	if(n < 2)
	{
		curr = n;
	}

	unsigned int i;
	for(i = 2; i <= n; i++)
	{
		curr = (prevPrev + prev)%FLOW;
		prevPrev = prev;
		prev = curr;
	}
	return curr;
}
