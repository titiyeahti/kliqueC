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

void print(int *t, int n)
{
				int i;
				for(i=0; i<n; i++)
								printf("%d ", t[i]);

				printf("\n");
}

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

int* graph_neighbourg(graph_p g, int i);


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
								printf("%d : ", i);
								int start, stop;
								start = g->vertices[i];
								stop = g->vertices[i+1];
								printf("%d [%d]: ", i, stop - start);

								for(j = start; j < stop; j++)
												printf("%d ", g->edges[j]);	

								printf("\n");
				}
}

void listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int* kdeg)
{
				int i;
				int j;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								for(i=0; i < size; i++)
												kdeg[sg[i]] ++;
								
								for(j=0; j<ck-1; j++)
												kdeg[clique[j]] += size;
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
																								ck, kdeg);
								}
				}

				free(sg);
}

int * kdeg(graph_p g, int k)
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
