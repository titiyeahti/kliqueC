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
				int* deg;
				int es;
				fp = fopen("../examples/skitter", "r");

				if(!fp)
								return EXIT_FAILURE;

				graph_p g = graph_from_file(fp);
				
/* 				printf("lu\n");
 * 
 * 				for (k=2; k<5; k++)
 * 				{
 * 								printf("%d\n",k);
 * 								deg = kdeg(g, k);
 * 								free(deg);
 * 				}
 */

				graph_free(g);

				return EXIT_SUCCESS;
}
