#include <stdio.h>

#define FLOW 65536

int main(void) {
	printf("%i\n", fib(1000000000000000000));  // why can't i do bigger numbers than this? - trying to run for a minute..
	return;
}

int fib(int n) {
	int prevPrev = 0; //~A[0]=0
	int prev = 1;		//!A[1]=1
	int curr = n;
//	int A[3]; // need to dynamically allocate space- BUT can just store the last 3 values
//	A[0] = 0;
//	A[1] = 1;

	int i, tmp;
	for(i = 2; i <= n; i++) {
		curr = (prevPrev + prev)%FLOW;  // curr gets value of this addition		
		prevPrev = prev;
		prev = curr;				//prev gets value of curr
		//prevPrev = tmp;
	}	
	return curr;
}