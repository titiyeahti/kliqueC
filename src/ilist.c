/*
 * =====================================================================================
 *
 *       Filename:  ilist.c
 *
 *    Description:  implementation of ilist.h
 *
 *        Version:  1.0
 *        Created:  12/02/2020 15:27:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - MPRI
 *
 * =====================================================================================
 */

#include "ilist.h"

/* should be tested (at least 1000 times) */
ilist ilist_move(ilist l1, ilist l2)
{
				if (l1 == NULL)
								return l2;

				ilist p1 = l1->prev;
				ilist n1 = l1->next;
				ilist p2;

				/* Maintaining the chain */
				if(p1 != NULL)
								p1->next = n1;
		
				if(n1 != NULL)
								n1->prev = p1;

				l1->next = l2;

				if (l2 != NULL)
				{
								p2 = l2->prev;

								if (p2 != NULL)
												p2->next = l1;
								
								l1->prev = p2;
								l2->prev = l1;
				}
				else 
								l1->prev = NULL;
								
				return l1;
}

void ilist_print(ilist l)
{
				if (l != NULL)
				{
								printf("%d ", l->val);
								ilist_print(l->next);
				}
				else
								printf("\n");
}

bucket bucket_new(int* deg, int m, int n)
{
				bucket res;
				ilist* by_deg;
				ilist* by_index;
				int i;

				by_deg = malloc(m*sizeof(ilist));
				by_index = malloc(n*sizeof(ilist));

				for(i=0; i<m; i++)
								by_deg[i] = NULL;

				for(i=0; i<n; i++)
				{
								by_index[i] = malloc(sizeof(elt));
								by_index[i]->val = i;
								by_index[i]->next = NULL;
								by_index[i]->prev = NULL;

								by_deg[deg[i]] = ilist_move(by_index[i], by_deg[deg[i]]);
				}

				res.n = n;
				res.m = m;
				res.by_deg = by_deg;
				res.by_index = by_index;

				return res;
}

int bucket_pop_min(bucket b)
{
				int i;
				ilist cur, next;

				for(i=0; i<b.m; i++)
				{
								if(b.by_deg[i] != NULL)
								{
												cur = b.by_deg[i];
												
												next = cur->next;
												if(next != NULL)
																next->prev = NULL;

												b.by_deg[i] = next;

												return cur->val;
								}
				}
				
				printf("error : bucket_pop_min, by_deg is empty\n");
				exit(EXIT_FAILURE);
}

void bucket_free(bucket b)
{
				int i;
				for(i=0; i<b.n; i++)
				{
								free(b.by_index[i]);
								b.by_index[i] = NULL;
				}

				free(b.by_deg);
				b.by_deg = NULL;
				free(b.by_index);
				b.by_index = NULL;
}

void bucket_print(bucket b)
{
				int i;
				for(i=0; i<b.m; i++)
				{
								printf("%d : ", i);
								ilist_print(b.by_deg[i]);
				}
}

void bucket_modify_deg(bucket b, int id, int deg, int ndeg)
{
				ilist cur = b.by_index[id];

				if(cur->prev == NULL)
								b.by_deg[deg] = cur->next;

				b.by_deg[ndeg] = ilist_move(cur, b.by_deg[ndeg]);
}
