/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  implemetation of graph.h
 *
 *        Version:  1.0
 *        Created:  14/02/2020 01:10:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "graph.h"

graph_p graph_from_file(FILE* fd)
{
				int n;
				int m;
				int error;
				int i, j, it;

				char trash[64];
				char trash2[64];

				error = fscanf(fd, "%% %s %s", trash, trash2);
				error = fscanf(fd, "%% %d %d %d", &m, &n, &i);

				graph_p g = malloc(sizeof(struct graph));
				g->n = n;
				g->vertices = malloc((n+1)*sizeof(int));
				g->edges = malloc(m*sizeof(int));

				for(i=0; i<n+1; i++)
								g->vertices[i] = 0;
				
				error = fscanf(fd, "%d %d", &i, &j);
				while(error != EOF)
				{
								if(i >= j)
												printf("warning: graph_from_file %s:%d, %d>=%d \n", 
																__FILE__, __LINE__, i, j);

								/* i because the end of the outgoing edges from i is stored in 
								 * at vertices[i+1] */
								g->edges[g->vertices[i]] = j-1;

								for(it = i; it < n+1; it ++)
												g->vertices[it] ++;
								
								error = fscanf(fd, "%d %d", &i, &j);

								if (g->vertices[n] % 1024 == 0)
												printf("%d\n", g->vertices[n]);

				}

				if(m != g->vertices[n])
								printf("error: graph_from_file %s:%d, number of edges is not valid %d!=%d\n", 
												__FILE__, __LINE__, m, g->vertices[n]);

				return g;
}

int graph_degre(graph_p g, int i)
{
				if (i>=g->n)
				{
								printf("error graph_degre %s:%d vertex not in the graph\n",
																__FILE__, __LINE__);
								exit(EXIT_FAILURE);
				}
				
				return g->vertices[i+1] - g->vertices[i];
}

void graph_free(graph_p g)
{
				free(g->vertices);
				free(g->edges);
				free(g);
}

void graph_print(graph_p g)
{
				int i, j;
				for(i=0; i<g->n; i++)
				{
								int start, stop;
								start = g->vertices[i];
								stop = g->vertices[i+1];
								printf("%d [%d]: ", i, stop - start);

								for(j = start; j < stop; j++)
												printf("%d ", g->edges[j]);	

								printf("\n");
				}
				printf("\n");
}

void print(int *t, int n)
{
				int i;
				for(i=0; i<n; i++)
								printf("%d ", t[i]);

				printf("\n");
}

void quicksort(int* t, int n)
{
				if (n > 0)
				{
								/* partitionning */
								int i, j, temp;

								j=0;
								for (i=0; i<n-1; i++)
								{
												if (t[i] < t[n-1])
												{				
																temp = t[j];
																t[j] = t[i];
																t[i] = temp;
																j++;
												}
								}
								/* at least as big as te pivot */
								/*replacing the pivot */
								temp = t[j];
								t[j] = t[n-1];
								t[n-1] = temp;

								quicksort(t, j);
								quicksort(t+j+1, n-j-1);
				}
}

int* inter(int* t1, int* t2, int n1, int n2, int* k)
{
				int i, j;
				int n;

				i = 0;
				j = 0;
				*k = 0;
				n = MIN(n1, n2);

				int t[n];

				while (i < n1 && j < n2)
				{
								if (t1[i] == t2[j])
								{
												t[*k] = t1[i];
												(*k)++;
												i++;
												j++;
								}
								else 
								{
												if (t1[i] < t2[j])
																i++;
												else 
																j++;
								}
				}


				int *res = malloc((*k)*sizeof(int));
				memcpy(res, t, (*k)*sizeof(int));
				
				return res;
}

int ind_id_min(int* t, int* ind, int n)
{
				if (n == 0)
								exit(EXIT_FAILURE);

				int i;
				int min; 
				int id;

				min = t[0];
				id = 0;

				for(i=0; i<n; i++)
				{
								if (ind[i] && t[i]<min)
								{
												id = i;
												min = t[i];
								}
				}

				return id;
}

/* here ind is and indicator function 
 * n  is the size of the input */
int* ind_inter(int* input, int* ind, int n, int* k)
{
				int i;
				int t[n];
				int* res;

				*k = 0;

				for(i=0; i<n; i++)
				{
								if (ind[input[i]])
								{
												t[*k] = input[i];
												(*k) ++;
								}
				}
				
				res = malloc((*k)*sizeof(int));
				memcpy(res, t, (*k)*sizeof(int));

				return res;
}

int ind_size(int* ind, int n)
{
				int i;
				int size;

				size = 0;

				for(i=0; i<n; i++)
				{
								if(ind[i])
											 size ++;	
				}

				return size;
}

void listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int* deg)
{
				int i;
				int j;

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
												int cur = sg[i];
												int* neigh = g->edges + g->vertices[cur];
												int n2 = g->vertices[cur+1] - 
																g->vertices[cur];
												int new_size;
												int* nsg = inter(sg, neigh, size, n2, &new_size);
												clique[ck-k] = sg[i];
												
												if(new_size > 0)
																listing(g, nsg, clique, new_size, k-1, 
																								ck, deg);
								}
				}

				free(sg);
}

void remove_listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int target, int* deg)
{
				int i;
				int j;
				int flag = 0;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								for(j=0; j<size; j++)
								{
												if(sg[j] == target)
												{
																flag = 1;
																break;
												}
								}

								for(j=0; j<ck-1; j++)
								{
												if(clique[j] == target)
												{
																flag = 2;
																break;
												}
								}

								if (flag)
								{
												if(flag == 2)
												{
																for(i=0; i < size; i++)
																				deg[sg[i]] --;
																
																for(j=0; j<ck-1; j++)
																				deg[clique[j]] -= (size);
												}
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
												int cur = sg[i];
												int* neigh = g->edges + g->vertices[cur];
												int n2 = g->vertices[cur+1] - 
																g->vertices[cur];
												int new_size;
												int* nsg = inter(sg, neigh, size, n2, &new_size);
												clique[ck-k] = cur;

												for(j=0; j<new_size; j++)
												{
																if(nsg[j] == target)
																{
																				flag = 1;
																				break;
																}
												}

												for(j=0; j< ck+1-k; j++)
												{
																if(clique[j] == target)
																{
																				flag = 1;
																				break;
																}
												}
												
												if((new_size > 0) && (flag))
																remove_listing(g, nsg, clique, new_size, k-1, 
																								ck, target, deg);
								}
				}
				free(sg);
}

int* kdeg(graph_p g, int k)
{
				int* sg = malloc(g->n*sizeof(int));
				int* deg = malloc(g->n*sizeof(int));
				int clique[k];
				int i;

				for(i=0; i<k; i++)
								clique[i] = -1;

				for (i=0; i<g->n; i++)
				{
								sg[i] = i;
								deg[i] = 0;
				}


				listing(g, sg, clique, g->n, k, k, deg);

				return deg; 
}

/* here ind is and indicator function */
float clique_density(graph_p g, int* ind)
{
				int i, j;
				int n, m;
				int start, stop;
				int dest;

				n = 0;
				m = 0;

				for(i=0; i<g->n; i++)
				{
								if(ind[i])
								{
												n++;
												
												start = g->vertices[i];
												stop = g->vertices[i+1];

												for(j=start; j<stop; j++)
												{
																dest = g->edges[j];

																if(ind[dest])
																				m++;
												}
								}
				}

				return (float) 2.*m / ((n-1)*n);
}

int* quasi_clique(graph_p g, int s, int k)
{
				int* deg;
				int* neigh;
				int* sg;
				int i, j, id;
				int size, size2;
				int ind[g->n];
				int* ind_b;
				float density, density_b;
				int clique[k];

				ind_b = malloc(g->n*sizeof(int));

				for(i=0; i<g->n; i++)
				{
								ind[i] = 1;
								ind_b[i] = 1;
				}

				density = clique_density(g, ind);
				density_b = density;

				deg = kdeg(g, k);

				/*-----------------------------------------------------------------------------
				 *  UNSAFE : Do not trust the code below.
				 *-----------------------------------------------------------------------------*/

				for(i=g->n; i>s; i--)
				{
								/* la */
								id = ind_id_min(deg, ind, g->n);

								/* removing cliques */
								for(j=0; j<id+1; j++)
								{
												if(ind[j])
												{
																clique[0] = j;
																size = g->vertices[j+1] - g->vertices[j];
																neigh = g->edges + g->vertices[j];

																sg = ind_inter(neigh, ind, size, &size2);

																remove_listing(g, sg, clique, size2, k-1, k, id, deg);
												}
								}

								ind[id] = 0;
								/* adjusting clique density */
								density = clique_density(g, ind);

								/* update the best */
								if(density > density_b)
								{
												memcpy(ind_b, ind, g->n*sizeof(int));
												density_b = density;
												
												if (density == 1.)
																break;
								}
				}
				return ind_b;
}
