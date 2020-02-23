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

/* Base struct of my double linked lists */
typedef struct elt{
				int val;
				struct elt* prev;
				struct elt* next;	
} elt;

/* Double linked lists of int */
typedef elt* ilist;

/* by_index[i] contains the ilist with val i
 * by_deg[i] contains the ilist of vertices of current des i
 * n, m are the sizes of the two previous arrays*/
typedef struct bucket{
				int n, m;
				ilist* by_index;
				ilist* by_deg;
} bucket;

/* Requires : l1 != NULL, l2->prev == NULL
 * moves l1 to the head of l2, makes all the links needed then returns l1
 * O(1) */
ilist ilist_move(ilist l1, ilist l2);

void ilist_print(ilist l);

/* Warning : allocates memory
 * Requires : all entries of deg must be posives
 * Returns a bucket with max deg m and n verices 
 * O(m+n) */
bucket bucket_new(int* deg, int m, int n);

/* Pops the vertices with the min deg of b
 * Worst case O(m) but should be constant in average */
int bucket_pop_min(bucket b);

/* Updates the b by moving the vertices id from degre deg to degre ndeg
 * O(1) */
void bucket_modify_deg(bucket b, int id, int deg, int ndeg);

void bucket_free(bucket b);

void bucket_print(bucket b);

#endif   /* ----- #ifndef ilist_INC  ----- */


