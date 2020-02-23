/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  graph structure
 *
 *        Version:  1.0
 *        Created:  14/02/2020 00:59:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#ifndef  graph_INC
#define  graph_INC

#include "array.h"

struct graph
{
				int n;
				int* vertices;
				int* edges;
};

typedef struct graph* graph_p;

/* Warning : Allocates memory;
 * Requires : fd must be a file descriptor of a file containing ;
 * an undirected unweighted graph;
 * Returns the graph corresponding to the file;
 * O(2*m) */
graph_p graph_from_file(FILE* fd);

/* Returns the degre of i in g;
 * O(1) */
int graph_degre(graph_p g, int i);

/* Returns the neighbors of i in g and sets k to the size of the returned array;
 * O(1) */
int* graph_neighbors(graph_p g, int i, int* k);

/* Warning : allocates memory;
 * Returns a graph with the same edges as g but reverted
 * O(n+m) */
graph_p graph_reverse(graph_p g);

/* Malloc
 * returns the concat of D_rev(i) and D_g(i)
 * neighbors in g are bigger
 * O(concat) */
int* graph_all_neighbors(graph_p g, graph_p rev, int i, int* k); 

void graph_free(graph_p g);

void graph_print(graph_p g);

#endif   /* ----- #ifndef graph_INC  ----- */
