/*
 * =====================================================================================
 *
 *       Filename:  heap.h
 *
 *    Description:  I needed a heap structre for the degrees, the values will be the 
 *    							indices and the keys the kdeg;
 *
 *        Version:  1.0
 *        Created:  19/02/2020 15:22:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */


#ifndef  heap_INC
#define  heap_INC

#include "array.h"

typedef struct heap{
				int* val;
				int* key;
				int n;
} heap;

typedef heap* heap_p;

/* val[i] <-> val[j]
 * key[i] <-> key[j] */
int heap_size(heap_p h);

void heap_swap(heap_p h, int i, int j);

/* O(logn) */
/* recursive with i increasing */
void heap_downtamp(heap_p h, int i);

/* O(logn) */
/* recursive with i decreasing */
void heap_uptamp(heap_p h, int i);

/* O(logn) */
void heap_add(heap_p h, int val, int key);

/* deg[i] -> heap_add(i, deg[i]) */
/* O(nlogn) */
heap_p heap_construct(int* deg, int n);

/* return the value of the litlest elt and remove it from the heap */
/* O(logn) */
int heap_pop(heap_p h);

int heap_minval(heap_p h);

/* O(logn) */
void heap_decrease_key(heap_p h, int key, int val, int k);

void heap_free(heap_p);

#endif   /* ----- #ifndef heap_INC  ----- */

