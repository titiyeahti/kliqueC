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
				struct elt* prev;
				struct elt* next;	
} elt;

typedef elt* ilist;

typedef struct bucket{
				int n, m;
				ilist* by_index;
				ilist* by_deg;
} bucket;

typedef struct ret{
				int val;
				ilist l;
} ret;

/* move l1 != NULL to the head of l2 */
ilist ilist_move(ilist l1, ilist l2);

void ilist_print(ilist l);

bucket bucket_new(int* deg, int m, int n);

int bucket_pop_min(bucket b);

void bucket_modify_deg(bucket b, int id, int deg, int ndeg);

void bucket_free(bucket b);

void bucket_print(bucket b);

#endif   /* ----- #ifndef ilist_INC  ----- */


