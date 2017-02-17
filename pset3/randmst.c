#include <stdio.h>
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


int main(int argc, char* argv[]) {
	// ./randmst 0 numpoints numtrials dimension
	//printf("%i\n", argc);
	if (argc != 5) {
		printf("usage: ./randmst 0 numpoints numtrials dimension\n");
		return 1;
	}
	for (int i = 0; i < argc; i++) {
		printf(" argv of %i is %s\n", i, argv[i]);
	}
}