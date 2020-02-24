/*
 * =====================================================================================
 *
 *       Filename:  array.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/02/2020 23:12:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "array.h"

void print(int* t, int n)
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
												/* at least as big as te pivot */
												if (t[i] < t[n-1])
												{				
																temp = t[j];
																t[j] = t[i];
																t[i] = temp;
																j++;
												}
								}
								/*replacing the pivot */
								temp = t[j];
								t[j] = t[n-1];
								t[n-1] = temp;

								quicksort(t, j);
								quicksort(t+j+1, n-j-1);
				}
}

int max(int* t, int n)
{
				int m = 0;
				int i;
				for(i=0; i<n; i++)
				{
								if(t[i] > m)
												m = t[i];
				}

				return m;
}

int contains(int* t, int i, int n)
{
				int j;
				for(j=0; j<n; j++)
				{
								if (t[j] == i)
												return 1;
				}
				return 0;
}

int dich_contains(int* t, int i, int n)
{
				int a = 0;
				int b = n;
				int m;

				while(b > a)
				{
								m = (a+b)>>1;
								
								if(t[m] == i)
												return 1;

								if(t[m] > i)
												b = m;
								else
												a = m+1;
				}
				return 0;
}

int log2(int i)
{
				int j;
				for(j=30; j<0; j--)
								if(i & (1<<j))
												return (j+1);

				/* i == 0 */
				return 0; 
}

/* n2 should be >> n1 */
int* dich_inter(int* t1, int* t2, int n1, int n2, int* k)
{
				int i;
				int t[n1];

				*k = 0;

				for(i=0; i<n1; i++)
				{
								if(dich_contains(t2, t1[i], n2))
								{
												t[*k] = t1[i];
												(*k) ++;
								}
				}
				if (*k == 0)
								return NULL;

				int *res = malloc((*k)*sizeof(int));
				memcpy(res, t, (*k)*sizeof(int));

				return res;
}

int* lin_inter(int* t1, int* t2, int n1, int n2, int* k)
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

				if (*k == 0)
								return NULL;

				int *res = malloc((*k)*sizeof(int));
				memcpy(res, t, (*k)*sizeof(int));

				return res;
}

int* inter(int* t1, int* t2, int n1, int n2, int* k)
{
				int* big;
				int* small;
				int nb, ns;

				if(n1>n2)
				{
								big = t1;
								small = t2;
								nb = n1;
								ns = n2;
				}
				else
				{
								big = t2;
								small = t1;
								nb = n2;
								ns = n1;
				}

				if((nb + ns) < ns*log2(nb))
								return lin_inter(t1, t2, n1, n2, k);
				else
								return dich_inter(small, big, ns, nb, k);

}

/* to TEST */
int* concat(int* t1, int* t2, int n1, int n2)
{
				int* res = malloc((n1+n2)*sizeof(int));

				memcpy(res, t1, n1*sizeof(int));
				memcpy(res+n1, t2, n2*sizeof(int));

				return res;
}


/*-----------------------------------------------------------------------------
 *  INDIC FUNCTION
 *-----------------------------------------------------------------------------*/

/*  to TEST */
int ind_contains(uchar* ind, int i)
{
				int spot = i>>3;
				int exp = i & 7;

				return (ind[spot] & (1<<exp)) >> exp;
}

void ind_on(uchar* ind, int i)
{
				int spot = i>>3;
				int exp = i & 7;

				ind[spot] |= (1<<exp);
}

void ind_off(uchar* ind, int i)
{
				int spot = i>>3;
				int exp = i & 7;

				ind[spot] &= ~(1<<exp);
}

int ind_id_min(int* t, uchar* ind, int n)
{
				if (n == 0)
								exit(EXIT_FAILURE);

				int i, min, id;

				min = (1<<30) + ((1<<30) - 1);

				for(i=0; i<n; i++)
				{
								if (ind_contains(ind, i) && t[i]<min)
								{
												id = i;
												min = t[i];

												if (min==0)
																return id;
								}
				}

				return id;
}

int* ind_inter(int* input, uchar* ind, int n, int* k)
{
				int i;
				int t[n];
				int* res;

				*k = 0;

				for(i=0; i<n; i++)
				{
								if(ind_contains(ind, input[i]))
								{
												t[*k] = input[i];
												(*k) ++; 
								}
				}

				if (*k == 0)
								return NULL;
				res = malloc((*k)*sizeof(int));
				memcpy(res, t, (*k)*sizeof(int));
				return res;
}

int ind_size(uchar* ind, int n)
{
				int i, j;
				int max = n>>3;
				int size = 0;

				for(i=0; i <= max; i++)
				{
								for(j=0; j<8; j++)
								{
												if (((i<<3) + j) < n)
																size += ind_contains(ind, (i<<3) + j);
								}
				}

				return size;
}

void ind_print(uchar* ind, int n)
{
				int i;
				for(i=0; i<n; i++)
								printf("%d ", ind_contains(ind, i));

				printf("\n");
}

