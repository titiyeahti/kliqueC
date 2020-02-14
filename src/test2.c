/*
 * =====================================================================================
 *
 *       Filename:  test2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/02/2020 02:57:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "graph.h"

int main(void)
{
				FILE* fp;
				fp = fopen("../examples/zebra", "r");

				if(!fp)
								return EXIT_FAILURE;

				graph_p g = graph_from_file(fp);

				graph_print(g);

				int* t = malloc(g->n*sizeof(int));
				int k;
				int kdeg[g->n];
 				int clique[4];

				for(k=0; k<g->n; k++)
				{
								t[k] = k;
								kdeg[k] = 0;
				}

				k = 2;
				listing(g, t, clique, g->n, k, k, kdeg);
				
				print(kdeg, g->n);

				t = malloc(g->n*sizeof(int));
				
				for(k=0; k<g->n; k++)
				{
								t[k] = k;
								kdeg[k] = 0;
				}

				k=3;
				listing(g, t, clique, g->n, k, k, kdeg);
				print(kdeg, g->n);
				
/* 				t = malloc(g->n*sizeof(int));
 * 
 * 				
 * 				for(k=0; k<g->n; k++)
 * 				{
 * 								t[k] = k;
 * 								kdeg[k] = 0;
 * 				}
 * 
 * 				k=4;
 * 				listing(g, t, clique, g->n, k, k, kdeg);
 * 				print(kdeg, g->n);
 * 				
 * 				t = malloc(g->n*sizeof(int));
 * 				
 * 				for(k=0; k<g->n; k++)
 * 				{
 * 								t[k] = k;
 * 								kdeg[k] = 0;
 * 				}
 * 
 * 				k=5;
 * 				listing(g, t, clique, g->n, k, k, kdeg);
 * 				print(kdeg, g->n);
 */
				graph_free(g);

				return EXIT_SUCCESS;
}
