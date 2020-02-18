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

/* must free the returned value at some point */
/* O(2*m) */
graph_p graph_from_file(FILE* fd);

/* O(1) */
int graph_degre(graph_p g, int i);

/* NO MALLOC be CAREFULL
 * O(1) */
int* graph_neighbourg(graph_p g, int i, int* k);

/* counting incomming edges to vertices
 * cummulative sum over vertices
 * adding the actual reverse edges
 * sort ? */
graph_p graph_reverse(graph_p g);

/* Malloc
 * returns the concat of D_rev(i) and D_g(i)
 * neighbourg in g are bigger
 * O(concat) */
int* graph_all_neighbourg(graph_p g, graph_p rev, int i, int* k); 

void graph_free(graph_p g);

void graph_print(graph_p g);

#endif   /* ----- #ifndef graph_INC  ----- */
