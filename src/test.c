/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test file for mgraph.c
 *
 *        Version:  1.0
 *        Created:  13/02/2020 01:16:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "mgraph.h"

int main(void)
{
				FILE* fp;

				fp = fopen("../examples/zebra", "r");

				if(!fp)
								return EXIT_FAILURE;

				mgraph_p g = mgraph_from_file(fp, 0);


				int k = 4;
				int* res;
				int b;


				res = kdeg(g, k);
				b = not_empty(res, g->n);
				

				free(res);
				
				mgraph_free(g);

				fclose(fp);

				return EXIT_SUCCESS;
}
