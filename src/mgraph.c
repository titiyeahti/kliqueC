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
								mgraph_remove_edge(g, j, i);
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
				int i, j;
				char trash[64];
				char trash2[64];


				error = fscanf(fd, "%% %s %s", trash, trash2);
				error = fscanf(fd, "%% %d %d %d", &j, &size, &i);

				mgraph_p g = mgraph_new(size);

				while(error != EOF)
				{
								error = fscanf(fd, "%d %d", &i, &j);
								mgraph_new_edge(g, i-1, j-1);
				}
				return g;
}

void mgraph_free(mgraph_p g)
{
				int i;
				for(i=0; i<g->n; i++)
				{
								ilist_free(g->v[i]->l);
								free(g->v[i]);
				}
				free(g->v);
				free(g);
				g = NULL;
}

/* typedef struct arg_base
 * {
 * 				int* res;
 * 				mgraph_p g;
 * 				ilist clique;
 * } arg_base;
 * 
 * void aux_base(int i, void* arg)
 * {
 * 				int* res = ((arg_base *) arg)->res;
 * 				mgraph_g g = ((arg_base *) arg)->g;
 * 				ilist clique = ((arg_base *) arg)->clique;
 * 
 * 
 * }
 */

void listing(mgraph_p g, ilist gr, ilist clique, int k, int* res)
{
				printf("gr :\n");
				ilist_print(gr);
				if (k == 2)
				{
								int size;
								ilist inter;
								ilist it1, it2;
								it1 = gr;
								/* O(n^2) */
								while (it1 != NULL)
								{
												/* neighbourg of i also in gr */
												inter = ilist_inter(g->v[it1->val]->l, gr);
												size = ilist_size(inter);
												if (size>0)
												{
																it2 = clique;
																res[it1->val] += size;
																while (it2 != NULL)
																{
																				res[it2->val] += size;
																				it2 = it2->next;
																}

																/* at least an elt */
																it2 = inter;
																while (it2 != NULL)
																{
																				res[it2->val] ++;
																				it2 = it2->next;
																}

												}

												ilist_free(inter);
												it1 = it1->next;
								}
								
								ilist_free(gr);
								ilist_free(clique);
				}

				else
				{
								ilist it = gr;
								int i;
								ilist inter;
								ilist nclique;
								/*  first step of rec */
								if (clique == NULL)
								{
												for(i=0; i<g->n; i++)
												{
																inter = ilist_copy(g->v[i]->l);
																
																if (inter != NULL)
																{
																				nclique = ilist_new(i);
																				listing(g, inter, nclique, k-1, res);
																}
																else 
																				ilist_free(inter);
												}
												
								}

								else
								{
												while (it != NULL)
												{
																printf("it->val = %d\n", it->val); 
																inter = ilist_inter(gr, g->v[it->val]->l);
																printf("inter:\n");
																ilist_print(inter);
																
																if (inter != NULL)
																{
																				nclique = ilist_add(ilist_copy(clique), it->val);
																				printf("nclique :\n");
																				ilist_print(nclique);
																				listing(g, inter, nclique, k-1, res);
																}
																else 
																				ilist_free(inter);

																it = it->next;
												}
								}
				}

				ilist_free(gr);
				ilist_free(clique);
}

int* kdeg(mgraph_p g, int k)
{
				int* res = malloc(g->n*sizeof(int));
				int i;
				for (i=0; i<g->n; i++)
								res[i] = 0;

				listing(g, NULL, NULL, k, res);

				return res;
}

int not_empty(int* res, int size)
{
				int i;
				for(i=0; i<size; i++)
				{
								if(res[i] > 0)
											 return 1;	
				}
				return 0;
}

void mgraph_print(mgraph_p g)
{
				int i;
				for(i=0; i<g->n; i++)
				{
								printf("%d [%d]: ", i, g->v[i]->size);
								if (g->v[i]->size == 0)
												printf("\n");
								ilist_print(g->v[i]->l);
				}
}
