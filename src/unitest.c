/*
 * =====================================================================================
 *
 *       Filename:  unitest.c
 *
 *    Description:  unit testing to try to debug
 *
 *        Version:  1.0
 *        Created:  15/02/2020 22:50:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "graph.h"

int main()
{
				/*-----------------------------------------------------------------------------
				 * ARRAY operation  
				 *-----------------------------------------------------------------------------*/

				/* inter */
				int i, id, k, size;
				int n = 10;
				int t1[n];
				int t2[n];
				int ind[n];

				for(i=0; i<n; i++)
				{
								t1[i] = i;
								t2[i] = 2*i;
								ind[i] = 1;
				}

				int* t3 = inter(t1, t2, n, n, &k);

				for(i=0; i < k; i++)
				{
								if(t3[i] != 2*i)
												printf("error in inter\n");
				}

				/* ind_id_min */

				t1[0] = 4; 
				t1[1] = 2; 
				t1[2] = 0; 
				t1[3] = 2; 
				t1[4] = 1; 
				t1[5] = 0; 
				t1[6] = 5; 
				t1[7] = 1; 
				t1[8] = 3; 
				t1[9] = 1; 

				id = ind_id_min(t1, ind, n);

				if(id != 2)
								printf("id = %d ind_id_min fails test1\n", id);

				ind[2] = 0;
				ind[5] = 0;
				
				id = ind_id_min(t1, ind, n);

				if(id != 4)
								printf("id = %d ind_id_min fails test2\n", id);

				/* ind_inter */
				ind[6] = 0;

				int k1;
				int* t4 = ind_inter(t3, ind, k, &k1);

				print(t4, k1);

				/* ind_size */
				size = ind_size(ind, n);

				if(size != n-3)
								printf("size = %d, ind_size fails test 1\n", size);

				free(t4);
				free(t3);

				print(ind, n);

				return 1;
}
