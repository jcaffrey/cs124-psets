#include <stdio.h>

int main(int argc, char* argv[]) {
	// ./randmst 0 numpoints numtrials dimension
	printf("%i\n", argc);
	if (argc != 4) {
		printf("usage: ./randmst 0 numpoints numtrials dimension\n");
	}
}