#include <stdio.h>

int count = 0;

int fib(int n);

int main(void) {
	printf("%i\n", fib(10));
	printf("got here with %i calls to fib\n", count);
	return;
}

int fib(int n) {
	count++;
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}
