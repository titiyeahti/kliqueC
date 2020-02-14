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

struct graph
{
				int n;
				int* vertices;
				int* edges;
};

typedef struct graph* graph_p;

void print(int* t, int n);

graph_p graph_from_file(FILE* fd);

int graph_degre(graph_p g, int i);

int* graph_neighbourg(graph_p g, int i);

void quicksort(int* t, int n);

int* inter(int* t1, int* t2, int n1, int n2, int* k);

void graph_free(graph_p g);

void graph_print(graph_p g);

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
 *  							k is decreasing during the recurssives calls but ck remains constant
 * =====================================================================================
 */
void listing(graph_p g, int* sg, int* clique, int size, int k, int ck, int* kdeg);

/* int* kdeg(graph_p g, int k);
 */

#endif   /* ----- #ifndef graph_INC  ----- */
