/*
 * =====================================================================================
 *
 *       Filename:  test3.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  15/02/2020 10:32:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "graph.h"
#include "time.h"

#define S 10

int main(int argc, char** argv)
{
				FILE* fp;
				int* ind;
				int k;
				clock_t t1, t2;
				
				if(argc != 2)
								fp = fopen("../examples/zebra", "r");
				else 
								fp = fopen(argv[1], "r");

				if(!fp)
								return EXIT_FAILURE;

				graph_p g = graph_from_file(fp);

				graph_print(g);

				printf("%% k size density time\n");
				for (k=2; k<3; k++)
				{
								t1 = clock();
								ind = quasi_clique(g, S, k);
								t2 = clock();
								print(ind, g->n);
								printf("%d %d %f %f\n", 
																k, ind_size(ind, g->n), 
																clique_density(g, ind),
																(double)(t2-t1)/CLOCKS_PER_SEC);

								free(ind);
				}

				graph_free(g);

				return EXIT_SUCCESS;
}
