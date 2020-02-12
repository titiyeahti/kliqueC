/*
 * =====================================================================================
 *
 *       Filename:  ilist.h
 *
 *    Description:  Integer chained lists
 *
 *        Version:  1.0
 *        Created:  12/02/2020 15:11:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - MPRI
 *
 * =====================================================================================
 */

#ifndef  ilist_INC
#define  ilist_INC

#include <stdio.h>
#include <stdlib.h>

typedef struct elt{
				int val;
				struct elt* next; 
}elt;

typedef elt* ilist;

ilist ilist_new(int i);

ilist ilist_add(ilist l, int i);

ilist ilist_copy(ilist l);

int ilist_contains(ilist l, int i);

ilist ilist_remove(ilist l, int i);

void ilist_iter(ilist l, void (* fun)(void*), void* arg);

void ilist_free(ilist l);

void ilist_print(ilist l);

#endif   /* ----- #ifndef ilist_INC  ----- */


