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
								int ck, int* deg, bucket b)
{
				int* neigh;
				int* nsg;
				int i, j;
				int cur;
				int neigh_size, nsg_size;
				int d;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								/* O(size) */
								for(i=0; i < size; i++)
								{
												d = deg[sg[i]];
												deg[sg[i]] --;
												bucket_modify_deg(b, sg[i], d, deg[sg[i]]);
								}

								/* updating the degre of the current target
								 * no need to update b since it have been deleted before */
								deg[clique[0]] -= size;

								/* O(1) */
								for(j=1; j<ck-1; j++)
								{
												d = deg[clique[j]];
												deg[clique[j]] -= size;
												bucket_modify_deg(b, clique[j], d, deg[clique[j]]);
								}
				}
				else 
				{
								for(i=0; i<size; i++)
								{
												cur = sg[i];
												neigh = graph_neighbors(g, cur, &neigh_size);
												nsg = inter(sg, neigh, size, neigh_size, &nsg_size);

												clique[ck-k] = cur;
												
												if(nsg_size > 0)
																remove_listing(g, nsg, clique, nsg_size, k-1, 
																								ck, deg, b);
								}
				}
				free(sg);
}

int* kdeg(graph_p g, int k)
{
				int* deg = malloc(g->n*sizeof(int));
				int clique[k];
				int i;

				for(i=0; i<g->n; i++)
								deg[i] = 0;

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
				int i, id;
				int neigh_size, sg_size, i_size;
				int n, m, max_deg;
				double rho, rho_b;

				i_size = ((g->n) >> 3) + 1;

				/* Some bits in the inds may be unused */
				int *deg, *neigh, *sg;
				int clique[k];
				uchar ind[i_size];
				uchar* ind_b;
				graph_p rev;
				
				bucket b;
				
				ind_b = malloc(i_size*sizeof(uchar));
				for(i=0; i<i_size; i++)
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

				max_deg = max(deg, n)+1;

				b = bucket_new(deg, max_deg, n);

				for(i=g->n; i>s; i--)
				{
								/* O(1) amortized complexity O(max_deg) otw */
								id = bucket_pop_min(b);

								/* updating the indicator */
								ind_off(ind, id);

								/* compute the neighbors of id in the current subgraph */
								neigh = graph_all_neighbors(g, rev, id, &neigh_size);
								sg = ind_inter(neigh, ind, neigh_size, &sg_size);
								free(neigh);

								/* removnig cliques if needed */
								if(deg[id] != 0)
								{
												clique[0] = id;
												remove_listing(g, sg, clique, sg_size, k-1, k, deg, b);
								}
								else 
												free(sg);

								/* adjusting clique density */
								m -= sg_size;
								n --;
								rho = density(n, m);

								/* update the best */
								if(rho > rho_b)
								{
												memcpy(ind_b, ind, i_size*sizeof(uchar));
												rho_b = rho;
												
												if (rho_b == 1.)
																break;
								}
				}

				free(deg);
				bucket_free(b);
				graph_free(rev);
				return ind_b;
}
