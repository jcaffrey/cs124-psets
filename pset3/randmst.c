#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graph.h"

// TODO: implement adjList representation

void generateGraph0(int n);
double randBelow1(void);

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

	if(dimension == 0)
		generateGraph0(512);
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
