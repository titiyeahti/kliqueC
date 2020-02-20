/*
 * =====================================================================================
 *
 *       Filename:  projet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/02/2020 23:48:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */
#include <time.h>
#include "projet.h"

void listing(graph_p g, int* sg, int* clique, int size, int k, int ck,
							 int to_free, int* deg)
{
				int i, j;
				int nsg_size, neigh_size;
				int cur, tf;
				int* neigh;
				int* nsg;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								for(i=0; i < size; i++)
												deg[sg[i]] ++;
								
								for(j=0; j<ck-1; j++)
												deg[clique[j]] += size;
				}
				else 
				{
								for(i=0; i<size; i++)
								{
												if (k != ck)
																cur = sg[i];
												else 
																cur = i;

												neigh = graph_neighbors(g, cur, &neigh_size);
												clique[ck-k] = cur;

												if(k != ck)
												{
																nsg = inter(sg, neigh, size, neigh_size, &nsg_size);
																tf = 1;
												}
												else
												{
																nsg = neigh;
																nsg_size = neigh_size;
																tf = 0;
												}
												
												
												if(nsg_size > 0)
																listing(g, nsg, clique, nsg_size, k-1, 
																								ck, tf, deg);
								}
				}
				
				if (to_free)
								free(sg);
}

/* Target is in clique, more precisely clique[0] = target */
void remove_listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int* deg, avl* a)
{
				int* neigh;
				int* nsg;
				int i, j;
				int cur;
				int neigh_size, nsg_size;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								elt e;

								/* O(size*logn) */
								for(i=0; i < size; i++)
								{
												e = elt_create(deg[sg[i]], sg[i]);
												*a = avl_remove(*a, e);
												
												deg[sg[i]] --;

												if(deg[sg[i]])
												{
																e.deg--;
																*a = avl_add(*a, e);
												}
								}

								/* O((ck-2)logn) */
								for(j=0; j<ck-1; j++)
								{
												if(j==0)
																deg[clique[j]] -= size;
												else
												{
																e = elt_create(deg[clique[j]], clique[j]);
																*a = avl_remove(*a, e);
																
																deg[sg[i]] -= size;

																if(deg[sg[i]])
																{
																				e.deg -= size;
																				*a = avl_add(*a, e);
																}
												}
								}
				}
				else 
				{
								for(i=0; i<size; i++)
								{
												cur = sg[i];
												neigh = graph_neighbors(g, i, &neigh_size);
												nsg = inter(sg, neigh, size, neigh_size, &nsg_size);

												clique[ck-k] = cur;
												
												if(nsg_size > 0)
																remove_listing(g, nsg, clique, nsg_size, k-1, 
																								ck, deg, a);
								}
				}
				free(sg);
}

int* kdeg(graph_p g, int k)
{
				int* deg = malloc(g->n*sizeof(int));
				int clique[k];
				int i;

				for(i=0; i<k; i++)
								clique[i] = -1;

				listing(g, NULL, clique, g->n, k, k, 0, deg);

				return deg; 
}

double density(int n, int m)
{
				return (double) 2.*m / ((double)(n-1)*(double)n);
}

/* here ind is and indicator function */
double clique_density(graph_p g, uchar* ind)
{
				int* neigh;
				int size;
				int i, j;
				int n, m;
				int dest;

				n = 0;
				m = 0;

				for(i=0; i<g->n; i++)
				{
								if(ind_contains(ind, i))
								{
												n++;
												
												neigh = graph_neighbors(g, i, &size);
												for(j=0; j<size; j++)
												{
																dest = neigh[j];

																if(ind_contains(ind, dest))
																				m++;
												}
								}
				}
				
				return density(n, m);
}

uchar* quasi_clique(graph_p g, int s, int k)
{
				clock_t t1, t2;
				float t_rest, t_ind, t_density; 
				int i, id;
				int neigh_size, sg_size, ind_size;
				int n, m;
				double rho, rho_b;

				ind_size = ((g->n) >> 3) + 1;

				/* Some bits in the inds may be unused */
				int *deg, *neigh, *sg;
				int clique[k];
				uchar ind[ind_size];
				uchar* ind_b;
				graph_p rev;
				
				/* avl */
				avl a;
				elt e;
				
				ind_b = malloc(ind_size*sizeof(uchar));

				for(i=0; i<ind_size; i++)
				{
								ind[i] = 255;
								ind_b[i] = 255;
				}
				
				n = g->n;
				m = g->vertices[n];
				rho = density(n, m);
				rho_b = rho;

				deg = kdeg(g, k);
				
				rev = graph_reverse(g);
				graph_print(g);
				graph_print(rev);

				a = avl_construct(deg, g->n);
				avl_print(a);
				printf("\n");

				for(i=g->n; i>s; i--)
				{
								/* O(logn) with a sorting like algo */
								e = avl_get_min(a);
								id = e.id;

								/* updating the indicator */
								ind_off(ind, id);

								/* removnig cliques if needed */
								if(deg[id] != 0)
								{
												if ((i&255) == 0)
																printf("id : %d\n", id);

												clique[0] = id;

												neigh = graph_all_neighbors(g, rev, id, &neigh_size);
												sg = ind_inter(neigh, ind, neigh_size, &sg_size);

												remove_listing(g, sg, clique, sg_size, k-1, k, deg, &a);
								}

								a = avl_remove(a, e);

								/* adjusting clique density */
								m -= (graph_degre(g, id) + graph_degre(rev, id));
								n --;
								rho = density(n, m);
								
								/* update the best */
								if(rho > rho_b)
								{
												memcpy(ind_b, ind, ind_size*sizeof(uchar));
												rho_b = rho;
												
												if (rho_b == 1.)
																break;
								}
				}

				avl_free(a);
				graph_free(rev);
				return ind_b;
}
