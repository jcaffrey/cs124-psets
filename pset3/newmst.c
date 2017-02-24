
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// void populateGraph(int n);  // implemented as adjacency list with dynamically resizing array to store edges

// TODO: implement adjList representation

// typedef struct vertex {
//     int id;
//     int weightFromP;  // if 0 is parent. distance to parent - ideally we sort our adjList by this
//     struct vertex *next;
//     int inMST;
// } *head;


typedef struct graph *Graph;


int main(int argc, char* argv[]) {
	time_t t; // to pass to srand to seed..
	srand((unsigned) time(&t));
	if (argc != 5) {
		printf("usage: ./randmst 0 numpoints numtrials dimension\n");
		return 1;
	}
	for (int i = 0; i < argc; i++) {
		printf(" argv of %i is %s\n", i, argv[i]);
	}
	int dimension = atoi(argv[4]);
	// graph_create(10);
	// if(dimension == 0)
	// 	generateGraph0(512);
}

Graph generateGraph(int dimension, )
