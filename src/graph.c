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

#include <time.h>
#include "graph.h"

graph_p graph_from_file(FILE* fd)
{
				int n;
				int m;
				int i, j;
				int count, temp, error;

				char trash[64];
				char trash2[64];

				error = fscanf(fd, "%% %s %s", trash, trash2);
				error = fscanf(fd, "%% %d %d %d", &m, &n, &i);

				if (error != 3)
								exit(EXIT_FAILURE);

				graph_p g = malloc(sizeof(struct graph));
				g->n = n;
				g->vertices = malloc((n+1)*sizeof(int));
				g->edges = malloc(m*sizeof(int));

				for(i=0; i<n+1; i++)
								g->vertices[i] = 0;
			

				/*-----------------------------------------------------------------------------
				 *  Vertices 
				 *-----------------------------------------------------------------------------*/
				i = 0;
				count = 0;
				while(fscanf(fd, "%d %d", &temp, &j) != EOF)
				{
								temp--;
								if (temp != i)
								{
												for (j=i+1; j<=temp; j++)
																g->vertices[j] = count;

												i = temp;
								}
								count++;
				}
				
				for (j=i+1; j<=n; j++)
								g->vertices[j] = count;

				/*-----------------------------------------------------------------------------*/

				rewind(fd);
				error = fscanf(fd, "%% %s %s", trash, trash2);
				error = fscanf(fd, "%% %d %d %d", &m, &n, &i);

				/*-----------------------------------------------------------------------------
				 *  Edges
				 *-----------------------------------------------------------------------------*/
				count = 0;
				while(fscanf(fd, "%d %d", &i, &j) != EOF)
				{
								g->edges[count] = j-1;
								count++;
				}
				/*-----------------------------------------------------------------------------*/

				if(m != g->vertices[n])
								printf("error: graph_from_file %s:%d, number of edges is not valid %d!=%d\n", 
												__FILE__, __LINE__, m, g->vertices[n]);

				return g;
}

int graph_degre(graph_p g, int i)
{
				return g->vertices[i+1] - g->vertices[i];
}

int* graph_neighbourg(graph_p g, int i, int *k)
{
				*k = graph_degre(g, i);
				return g->edges + g->vertices[i];
}

graph_p graph_reverse(graph_p g)
{
				int count[g->n];
				int* vertices;
				int* edges;
				int i, j;
				int index, nb;
				graph_p rev;
				vertices = malloc((g->n+1)*sizeof(int));
				edges = malloc(g->vertices[g->n]*sizeof(int));

				/* O(n) */
				for(i=0; i<g->n; i++)
								count[i] = 0;

				/* O(m) */
				for(i=0; i<g->vertices[g->n]; i++)
								count[g->edges[i]] ++;

				/* O(n) */
				vertices[0] = 0;
				for(i=1; i<=g->n; i++)
								vertices[i] = vertices[i-1] + count[i-1];

				/* O(m) */
				for(i=0; i<g->n; i++)
				{
								for(j = g->vertices[i]; j<g->vertices[i+1]; j++)
								{
												index = g->edges[j];
												nb = vertices[index+1] - count[index];
												edges[nb] = i;
												count[index] --;
								}
				}

				rev = malloc(sizeof(struct graph));
				rev->n = g->n;
				rev->vertices = vertices;
				rev->edges = edges;

				return rev;
}

int* graph_all_neighbourg(graph_p g, graph_p rev, int i, int* k)
{
				int* res;
				int n1, n2;
				int* v1;
				int* v2;

				v1 = graph_neighbourg(rev, i, &n1);
				v2 = graph_neighbourg(g, i, &n2);

				res = concat(v1, v2, n1, n2);
				*k = n1 + n2;

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
