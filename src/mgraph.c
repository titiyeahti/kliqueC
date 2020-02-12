/*
 * =====================================================================================
 *
 *       Filename:  mgraph.c
 *
 *    Description:  implementation of mgraph.h
 *
 *        Version:  1.0
 *        Created:  12/02/2020 16:30:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - MPRI
 *
 * =====================================================================================
 */

#include "mgraph.h"

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)>(b) ? (b) : (a))

mgraph_p mgraph_new(int size)
{
				mgraph_p g;
				g = malloc(sizeof(struct mgraph));

				g->n = size;
				g->v = malloc(size*sizeof(adjp));

				int i;
				for (i=0; i<size; i++)
				{
								g->v[i] = malloc(sizeof(adjl));
								g->v[i]->size = 0;
								g->v[i]->l = NULL;
				}
				return g;
}

void mgraph_resize(mgraph_p g, int size)
{
				if (size > g->n)
				{
								adjp* temp = malloc(size*sizeof(adjp));
								memcpy(temp, g->v, g->n);
								
								int i;
								for (i=g->n; i<size; i++)
								{
												temp[i] = malloc(sizeof(adjl));
												temp[i]->size = 0;
												temp[i]->l = NULL;
								}

								free(g->v);
								g->v = temp;
				}
}

void mgraph_remove_edge(mgraph_p g, int i, int j)
{
				/* +1 because we will use the indices i and j */
				int m = MAX(i,j)+1;

				if (m > g->n)
								mgraph_resize(g, m);

				if (ilist_contains(g->v[i]->l, j))
				{
								g->v[i]->l = ilist_remove(g->v[i]->l, j);
								g->v[i]->size --;
				}
}

void mgraph_new_edge(mgraph_p g, int i, int j)
{
				int m = MAX(i,j)+1;

				if (m > g->n)
								mgraph_resize(g, m);

				/* need to check invariant to maybe save some computations */
				if (i < j)
				{
								m_graph_remove_edge(g, j, i);
								/* if the edge does not already exists */
								if ( !ilist_contains(g->v[i]->l, j) )
								{
												g->v[i]->l = ilist_add(g->v[i]->l, j);
												g->v[i]->size ++;
								}
				}
				if (j < i)
				{
								/* if the graph contains netiher of (i, j) nor (j, i)
								 * witch is primary */
								if ( !(ilist_contains(g->v[i]->l, j) ||
																				ilist_contains(g->v[j]->l, i)) )
								{
												g->v[i]->l = ilist_add(g->v[i]->l, j);
												g->v[i]->size ++;
								}
				}
}

mgraph_p mgraph_from_file(FILE* fd, char config)
{
				int size;
				int error;

				fscanf(fd, "\% %s %s", NULL, NULL);
				fscanf(fd, "\% %d %d %d", NULL, &size, NULL);
				
}
