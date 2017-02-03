#include <stdio.h>

#define FLOW 65536

unsigned int fib(unsigned int n);

unsigned int main(void) 
{
	printf("%d\n", fib(100));  //10000000000000 why can't i do bigger numbers than this? - trying to run for a minute..
	return;
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