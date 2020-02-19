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
				int new_size, n2;
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

												neigh = graph_neighbors(g, cur, &n2);
												clique[ck-k] = cur;

												if(k != ck)
												{
																nsg = inter(sg, neigh, size, n2, &new_size);
																tf = 1;
												}
												else
												{
																nsg = neigh;
																new_size = n2;
																tf = 0;
												}
												
												
												if(new_size > 0)
																listing(g, nsg, clique, new_size, k-1, 
																								ck, tf, deg);
								}
				}
				
				if (to_free)
								free(sg);
}

void remove_listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int target, int* deg)
{
				int* neigh;
				int* nsg;
				int i, j;
				int cur;
				int n2, new_size;
				int flag = 0;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								flag += contains(sg, target, size);
								flag += contains(clique, target, ck-1) << 1;

								if (flag)
								{
												/* target is in clique */
												if(flag == 2)
												{
																for(i=0; i < size; i++)
																				deg[sg[i]] --;
																
																for(j=0; j<ck-1; j++)
																				deg[clique[j]] -= (size);
												}
												/* target is not in clique */
												else 
												{
																deg[target] --;
																for(j=0; j<ck-1; j++)
																				deg[clique[j]] --;
												}
								}
				}
				else 
				{
								for(i=0; i<size; i++)
								{
												cur = sg[i];
												neigh = graph_neighbors(g, i, &n2);
												nsg = inter(sg, neigh, size, n2, &new_size);
												clique[ck-k] = cur;

												flag += contains(sg, target, size);
												flag += contains(clique, target, ck-k+1) << 1;
												
												if((new_size > 0) && (flag))
																remove_listing(g, nsg, clique, new_size, k-1, 
																								ck, target, deg);
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

/* here ind is and indicator function */
double clique_density(graph_p g, uchar* ind)
{
				int* neigh;
				int size;
				int i, j;
				int n, m;
				int dest;
				double res;

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

				res = (double) 2.*m / ((double)(n-1)*(double)n);
				
				if (res < 0.)
								printf("(n, m) = (%d, %d) clique_density = %f\n", 
																n, m, res);

				return res;
}

uchar* quasi_clique(graph_p g, int s, int k)
{
				clock_t t1;
				int i, id;
				int neigh_size, sg_size, ind_size;
				double density, density_b;

				ind_size = ((g->n) >> 3) + 1;

				/* Some bits in the inds may be unused */
				int *deg, *neigh, *sg;
				int clique[k];
				uchar ind[ind_size];
				uchar* ind_b;
				graph_p rev;
				
				ind_b = malloc(ind_size*sizeof(uchar));

				for(i=0; i<ind_size; i++)
				{
								ind[i] = 255;
								ind_b[i] = 255;
				}

				density = clique_density(g, ind);
				density_b = density;

				t1 = clock();
				deg = kdeg(g, k);
				t1 = clock() - t1;
				printf("kdeg : %f s\n", (float)t1/CLOCKS_PER_SEC);

				t1 = clock();
				rev = graph_reverse(g);
				t1 = clock() - t1;
				printf("reverse graph : %f s\n", (float)t1/CLOCKS_PER_SEC);

				for(i=g->n; i>s; i--)
				{
								id = ind_id_min(deg, ind, g->n);

								/* removnig clique if needed */
								if(deg[id] != 0)
								{
												if (i&255 == 0)
																printf("id : %d\n", id);

												neigh = graph_all_neighbors(g, rev, id, &neigh_size);
												sg = ind_inter(neigh, ind, neigh_size, &sg_size);

												remove_listing(g, sg, clique, sg_size, k, k, id, deg);
								}

								/* updating the indicator */
								ind_off(ind, id);

								/* adjusting clique density */
								density = clique_density(g, ind);
								
								/* update the best */
								if(density > density_b)
								{
												memcpy(ind_b, ind, ind_size*sizeof(uchar));
												density_b = density;
												
												if (density == 1.)
																break;
								}
				}

				graph_free(rev);
				return ind_b;
}
