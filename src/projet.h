/*
 * =====================================================================================
 *
 *       Filename:  projet.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/02/2020 22:44:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#ifndef  projet_INC
#define  projet_INC

#include "graph.h"
#include "array.h"

void listing(graph_p g, int* sg, int* clique, int size, int k, int ck, 
								int to_free, int* deg);

void remove_listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int target, int* deg);

int* kdeg(graph_p g, int k);

double clique_density(graph_p g, int* ind);

int* quasi_clique(graph_p g, int s, int k);

#endif   /* ----- #ifndef projet_INC  ----- */