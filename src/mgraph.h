/*
 * =====================================================================================
 *
 *       Filename:  mgraph.h
 *
 *    Description:  unweighted and (un)-directed graphs with adjacency lists
 *
 *        Version:  1.0
 *        Created:  12/02/2020 16:04:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - MPRI
 *
 * =====================================================================================
 */

#ifndef  mgraph_INC
#define  mgraph_INC

#include "ilist.h"
#include <string.h>

typedef struct adjl
{
				int size;
				ilist l;
} adjl;

typedef adjl* adjp;

struct mgraph
{
				int n;
				adjp* v;
}

typedef struct mgraph* mgraph_p;

mgraph_p mgraph_new(int size);

void mgraph_resize(mgraph_p, int size);

void mgraph_remove_edge(mgraph_p g, int i, int j);

void mgraph_new_edge(mgraph_p g, int i, int j);

mgraph_p mgraph_from_file(FILE* fd, char config);

void mgraph_free(mgraph_p g);

void mgraph_print(mgraph_p g);

#endif   /* ----- #ifndef mgraph_INC  ----- */
