/**
*  
*
*
*
*
*
*
*/


//TODO:
// generate the 3 types of graphs:

	// • Complete graphs on n vertices, where the weight of each edge is a real number chosen uniformly at
	// random on [0, 1].
	// • Complete graphs on n vertices, where the vertices are points chosen uniformly at random inside the
	// unit square. (That is, the points are (x, y), with x and y each a real number chosen uniformly at
	// random from [0, 1].) The weight of an edge is just the Euclidean distance between its endpoints.
	// • Complete graphs on n vertices, where the vertices are points chosen uniformly at random inside the
	// unit cube (3 dimensions) and hypercube (4 dimensions). As with the unit square case above, the
	// weight of an edge is just the Euclidean distance between its endpoints.

// GOAL 1 : determine, for each type of graph, how the avg weight of the MST grows as a fn of n
	// implement an MST algo
	// implement procedures that generate the random graphs

// GOAL 2 : for each type of graph, plot the values
	// choose some values of n
	// for each value of n, run code on several randomly chosen instances of size n and compute avg value for runs
	// give a function f(n) that describes the plot, including constant factors
		// Run your program for n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072, and larger
		// values, if your program runs fast enough. (Having your code handle up to at least n = 131072 vertices
		// is one of the assignment requirements; going up to only smaller n will hurt your score on the assignment.
		// Getting up to 65536 will result in only a very small loss of points.) Run each value of n at least five times
		// and take the average. (Make sure you re-seed the random number generator appropriately!)


// GOAL 3 : design tests that prove correctness

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generateGraph1(int n);
double randBelow1(void);

int main(int argc, char* argv[]) {
	// ./randmst 0 numpoints numtrials dimension
	//printf("%i\n", argc);
	time_t t; // to pass to srand to seed..   
	srand((unsigned) time(&t));


	if (argc != 5) {
		printf("usage: ./randmst 0 numpoints numtrials dimension\n");
		return 1;
	}
	for (int i = 0; i < argc; i++) {
		printf(" argv of %i is %s\n", i, argv[i]);
	}
	//printf("%i\n", (int) *argv[3]);
	int dimension = atoi(argv[4]);

	if(dimension == 0)
		generateGraph1(512);
	//if(dimension == 2)
	//	generateBoxGraph(10);
}

double rand0to1(void) {
	return (double) rand() / (double) RAND_MAX;
}

void generateGraph1(int n) {
	double adj_mat[n][n];
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if (i == j) {
				adj_mat[i][j] = 0.0;
			}
			else {
				adj_mat[i][j] = rand0to1();
			}
		}
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j< n; j++) {
			printf("%f\n", adj_mat[i][j]);
		}
	}

}

