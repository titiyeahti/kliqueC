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

ilist ilist_new(int i)
{
				ilist l;
				l = malloc(sizeof(elt));

				l->val = i;
				l->next = NULL;

				return l;
}

ilist ilist_add(ilist l, int i)
{
				ilist nl;
				nl = malloc(sizeof(elt));

				nl->val = i;
				nl->next = l;

				return nl;
}

ilist ilist_copy(ilist l)
{
				if (l == NULL)
								return NULL;
				else 
								return ilist_add(ilist_copy(l->next), l->val);
}

int ilist_contains(ilist l, int i)
{
				if (l == NULL)
								return 0;
				else 
				{
								return l->val == i || ilist_contains(l->next, i);
				}
}

ilist ilist_remove(ilist l, int i)
{
				if (l == NULL)
								return NULL;
				else 
				{
								if (l->val == i)
								{
												ilist nl = l->next;
												free(l);
												return nl;
								}
								else 
								{
												l->next = ilist_remove(l->next, i);
												return l;
								}
				}
}

ilist ilist_iter(ilist l, void (* fun)(int, void*), void* arg)
{
				if (l != NULL)
				{
								fun(l->val, arg);
								ilist_iter(l->next, fun, arg);
				}
}

void ilist_free(ilist l)
{
				if (l != NULL)
				{
								ilist_free(l->next);
								free(l);
								l = NULL;
				}
}

void ilist_print(ilist l)
{
				if (l != NULL)
				{
								if (l->next == NULL)
												printf("%d\n", l->val);
								else
								{
												printf("%d, ", l->val);
												ilist_print(l->next);
								}
}
