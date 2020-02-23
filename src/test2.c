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

#include "projet.h"
#include <time.h>

int main(void)
{
				FILE* fp;
				int* deg;
				int k;
				clock_t t;

				free(NULL);

				fp = fopen("../examples/zebra", "r");

				if(!fp)
								return EXIT_FAILURE;

				graph_p g = graph_from_file(fp);
				fclose(fp);
				
				printf("lu\n");

				for (k=2; k<5; k++)
				{
								t = clock();
								deg = kdeg(g, k);
								t = clock() - t;
								printf("%d %f\n",k, (float)t/CLOCKS_PER_SEC);
								free(deg);
				}


				graph_free(g);

				return EXIT_SUCCESS;
}
