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

				ilist l = NULL;
				ilist l2;
				l = ilist_add(l, 1);
				l = ilist_add(l, 2);
				l = ilist_add(l, 3);
				l = ilist_add(l, 4);
				l = ilist_add(l, 5);

				l2 = ilist_copy(l);

				ilist_print(l2);

				fp = fopen("../examples/zebra", "r");

				if(!fp)
								return EXIT_FAILURE;

				mgraph_p g = mgraph_from_file(fp, 0);
				mgraph_print(g);


				int k = 4;
				int* res;
				int b;

				printf("b4 kdeg\n");

				res = kdeg(g, k);
				b = not_empty(res, g->n);
				
				printf("After kdeg\n");

				free(res);

				printf("%d\n", b);

				mgraph_free(g);

				fclose(fp);

				return EXIT_SUCCESS;
}
