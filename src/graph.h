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

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)>(b) ? (b) : (a))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*-----------------------------------------------------------------------------
 *  GRAPHS
 *-----------------------------------------------------------------------------*/

struct graph
{
				int n;
				int* vertices;
				int* edges;
};

typedef struct graph* graph_p;

/* must free the returned value at some point */
graph_p graph_from_file(FILE* fd);

int graph_degre(graph_p g, int i);

/* DO NOT USE, It does not work */
int* graph_neighbourg(graph_p g, int i);

void graph_free(graph_p g);

void graph_print(graph_p g);


/*-----------------------------------------------------------------------------
 *  Arrays and set operations
 *-----------------------------------------------------------------------------*/

void print(int* t, int n);

void quicksort(int* t, int n);

/* must free the returned value at some point */
int* inter(int* t1, int* t2, int n1, int n2, int* k);

/* indicator function */

int ind_id_min(int* t, int* ind, int n);

/* must free the returned value at some point */
int* ind_inter(int* input, int* ind, int n, int* k);

int ind_size(int* ind, int);

/*-----------------------------------------------------------------------------
 *  PROJET functions
 *-----------------------------------------------------------------------------*/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  listing
 *  Description:  implementaiton of the listing funciton presented in the paper,
 *  							- g : base graph;
 *  							- sg : sorted array of size size representing the current subgraph;
 *  							- clique : current clique represented as an array of size ck;
 *  							- k : the size of the clique that we want;
 *  							- kdeg : the array of clique degre for g, updated at the end of the 
 *  										recursion.
 *
 *  							k is decreasing during the recursives calls but ck remains constant
 * =====================================================================================
 */
void listing(graph_p g, int* sg, int* clique, int size, int k, int ck, 
								int to_free, int* deg);

void remove_listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int target, int* deg);

int* kdeg(graph_p g, int k);

float clique_density(graph_p g, int* ind);

int* quasi_clique(graph_p g, int s, int k);

#endif   /* ----- #ifndef graph_INC  ----- */
