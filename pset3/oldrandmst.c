
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// void populateGraph(int n);  // implemented as adjacency list with dynamically resizing array to store edges


/* basic directed graph type */

typedef struct graph *Graph;

/* create a new graph with n vertices labeled 0..n-1 and no edges */
Graph graph_create(int n);

/* free all space used by graph */
void graph_destroy(Graph);

/* add an edge to an existing graph */
/* doing this more than once may have unpredictable results */
/* second version specifies edge weight */
/* (first version defaults to GRAPH_DEFAULT_EDGE_WEIGHT) */
#define GRAPH_DEFAULT_EDGE_WEIGHT (1)
void graph_add_edge(Graph, int source, int sink);
void graph_add_weighted_edge(Graph, int source, int sink, int weight);

/* return the number of vertices/edges in the graph */
int graph_vertex_count(Graph);
int graph_edge_count(Graph);

/* return the out-degree of a vertex */
int graph_out_degree(Graph, int source);

/* return 1 if edge (source, sink) exists), 0 otherwise */
int graph_has_edge(Graph, int source, int sink);

/* return weight of edge, or MAXINT (from values.h) if edge doesn't exist */
int graph_edge_weight(Graph, int source, int sink);

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
/* no particular order is guaranteed */
void graph_foreach(Graph g, int source,
        void (*f)(Graph g, int source, int sink, void *data),
        void *data);

/* like above but also supplies weight */
void graph_foreach_weighted(Graph g, int source,
        void (*f)(Graph g, int source, int sink, int weight, void *data),
        void *data);

// TODO: implement adjList representation

struct graph {
    int n;              /* number of vertices */
    int m;              /* number of edges */
    struct successors {
        int d;          /* number of successors */
        int len;        /* number of slots in array */
        char is_sorted; /* true if list is already sorted */
        struct edge {
            int sink;           /* other end of edge */
            int weight;         /* used for shortest-path algorithms */
        } list[1];    /* actual list of successors */
    } *alist[1];
};

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

	graph_create(10);
	// if(dimension == 0)
	// 	generateGraph0(512);
}

/* create a new graph with n vertices labeled 0..n-1 and no edges */
Graph
graph_create(int n)
{
    Graph g;
    int i;

    g = malloc(sizeof(struct graph) + sizeof(struct successors *) * (n-1));
    assert(g);

    g->n = n;
    g->m = 0;

    for(i = 0; i < n; i++) {
        g->alist[i] = malloc(sizeof(struct successors));
        assert(g->alist[i]);

        g->alist[i]->d = 0;
        g->alist[i]->len = 1;
        g->alist[i]->is_sorted= 1;
    }

    return g;
}

/* free all space used by graph */
void
graph_destroy(Graph g)
{
    int i;

    for(i = 0; i < g->n; i++) free(g->alist[i]);
    free(g);
}

/* add an edge to an existing graph */
void
graph_add_weighted_edge(Graph g, int u, int v, int wt)
{
    assert(u >= 0);
    assert(u < g->n);
    assert(v >= 0);
    assert(v < g->n);

    /* do we need to grow the list? */
    while(g->alist[u]->d >= g->alist[u]->len) {
        g->alist[u]->len *= 2;
        g->alist[u] =
            realloc(g->alist[u],
                sizeof(struct successors) + sizeof(struct edge) * (g->alist[u]->len - 1));
    }

    /* now add the new sink */
    g->alist[u]->list[g->alist[u]->d].sink = v;
    g->alist[u]->list[g->alist[u]->d].weight = wt;
    g->alist[u]->d++;
    g->alist[u]->is_sorted = 0;

    /* bump edge count */
    g->m++;
}
/* return the number of vertices in the graph */
int
graph_vertex_count(Graph g)
{
    return g->n;
}

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
void
graph_foreach_weighted(Graph g, int source,
    void (*f)(Graph g, int source, int sink, int weight, void *data),
    void *data)
{
    int i;

    assert(source >= 0);
    assert(source < g->n);

    for(i = 0; i < g->alist[source]->d; i++) {
        f(g, source,
                g->alist[source]->list[i].sink,
                g->alist[source]->list[i].weight,
                data);
    }
}

// READ DIJKSTRA stuff..


double rand0to1(void) {
	return (double) rand() / (double) RAND_MAX;
}
























// void generateGraph1(int n) {
// 	double adj_mat[n][n];
// 	int i, j;
// 	for(i = 0; i < n; i++) {
// 		for(j = 0; j < n; j++) {
// 			if (i == j) {
// 				adj_mat[i][j] = 0.0;
// 			}
// 			else {
// 				adj_mat[i][j] = rand0to1();
// 			}
// 		}
// 	}
// 	for(i = 0; i < n; i++) {
// 		for(j = 0; j< n; j++) {
// 			printf("%f\n", adj_mat[i][j]);
// 		}
// 	}
//
// }


//
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <math.h>
// #include <assert.h>
//
// struct graph {
//     int n;
//     int dimension; // 0, 2, 3, 4
//     struct adjList {
//         int vertexId;
//         int numNbrs;
//         int len;        /* number of slots in array */
//         int x;
//         int y;
//         int z;
//         int w;
//         struct edge {
//             int nbrId;
//             int weightFromP;
//             // int sink;           /* other end of edge */
//             // int weight;         /* used for shortest-path algorithms */
//         } edges[1];    /* actual list of successors */
//     } *vertices[1];
// };
//
// typedef struct graph *Graph;
//
// //void populateGraph0(int n);  // implemented as adjacency list with dynamically resizing array to store edges
// Graph generateGraph(int n, int dimension);
// void addEdge(Graph g, int src, int dest, int dimension);
// double calculateEdgeWeight(Graph g, int src, int dimension);
//
//
//
// int main(int argc, char* argv[]) {
//     time_t t; // to pass to srand to seed..
//     t = now();
// 	srand((unsigned) time(&t));
// 	if (argc != 5) {
// 		printf("usage: ./randmst 0 numpoints numtrials dimension\n");
// 		return 1;
// 	}
// 	for (int i = 0; i < argc; i++) {
// 		printf(" argv of %i is %s\n", i, argv[i]);
// 	}
// 	int dimension = atoi(argv[4]);
//     printf("%i\n", dimension);
//     Graph e = generateGraph(10, dimension);
//     addEdge(e, 1, 2, dimension);
//     // graph_create(10);
// 	// if(dimension == 0)
// 	// 	populateGraph0(512);
// }
//
// // create vertices of graph
// Graph generateGraph(int n, int dimension)
// {
//     Graph g;
//     int i;
//
//     g = malloc(sizeof(struct graph) + sizeof(struct adjList *) * n - 1);
//     assert(g);
//
//     g->n = n;
//
//     for(i = 0; i < n; i++) {
//         g->vertices[i] = malloc(sizeof(struct adjList));
//         assert(g->vertices[i]);
//
//         g->vertices[i]->vertexId = i;
//         g->vertices[i]->numNbrs = 0;
//         g->vertices[i]->len = 1;
//         // keep this sorted?
//     }
//     return g;
// }
//
// void addEdge(Graph g, int src, int dest, int dimension)
// {
//     if (dimension == 0)
//         printf("dimesnio is zero! : %i\n", dimension);
//
//     while(g->vertices[src]->numNbrs >= g->vertices[src]->len)
//     {
//         g->vertices[src]->len *= 2;
//         g->vertices[src] = realloc(g->vertices[src], sizeof(struct edge) * (g->vertices[src]->len - 1) + sizeof(struct adjList));
//     }
//
//     g->vertices[src]->edges[g->vertices[src]->numNbrs].weightFromP = calculateEdgeWeight(g, src, dimension);
//     g->vertices[src]->edges[g->vertices[src]->numNbrs].nbrId = dest;
//     g->vertices[src]->numNbrs++;
//     // mark as not sorted?
//     //g->edges[src]->numNbrs += 1;
//     // g's edge count++?
//     return;
// }
//
// double calculateEdgeWeight(Graph g, int src, int dimension) {
//     if (dimension == 0) {
//         double newX;
//         double newY;
//         double test;
//         int r;
//         int newR;
//         rand();
//         newR = rand();
//         printf("RAND() IS : %i\n", r);
//         printf("newR IS : %i\n", newR);
//
//         newX = (double) newR / (double) RAND_MAX;
//         // newY = (double) rand() % 1.0;
//         // newY = rand();
//         // test = rand();
//
//         printf("newX IS : %f\n", newX);
//         // printf("newY: %f\n", newY);
//         // printf("test: %f\n", test);
//
//     }
//     return 0.5;
// }
//
