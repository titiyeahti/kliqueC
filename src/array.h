/*
 * =====================================================================================
 *
 *       Filename:  array.h
 *
 *    Description:  Some functions concerning (sorted) arrays.
 *
 *        Version:  1.0
 *        Created:  18/02/2020 22:46:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#ifndef  array_INC
#define  array_INC

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)>(b) ? (b) : (a))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char uchar;

/* Prints an int array of size n;
 * O(n) */
void print(int* t, int n);

/* Sorts an array of size n;
 * O(nlogn) */
void quicksort(int* t, int n);

/* Returns the max value of an array of size n;
 * O(n) */
int max(int* t, int n);

/* Returns 1 if i is in t, 0 otherwise;
 * O(n) */
int contains(int* t, int i, int n);

/* Require : t must be sorted;
 * Returns 1 if i is in t, 0 otherwise;
 * O(logn) */
int dich_contains(int* t, int i, int n);

/* Warning : Allocate memory,;
 * Requires : t1 and t2 must be sorted, k must not be NULL;
 * Returns an the intersection of t1 and t2;
 * Set the value of k to the size of the returned array;
 * if n1 > n2 : max(n1+n2), n2log(n1) */
int* inter(int* t1, int* t2, int n1, int n2, int* k);

/* Warning : Allocate memory,;
 * Requires : t1 and t2 must be sorted, t1[n1-1] < t2[0];
 * Returns an the concatenation of t1 and t2;
 * ~O(1) (malloc+memcpy) */
int* concat(int* t1, int* t2, int n1, int n2);

/* indicator function */
/* no protection nor size of the indicator function since it will 
 * always be of size n (the number of vertices) and every int we consider 
 * is less than n */

/* Requires : there must be at least i bits in ind;
 * Returns 1 if i is in ind, 0 otherwise;
 * O(1) */
int ind_contains(uchar* ind, int i);

/* Requires : there must be at least i bits in ind;
 * Sets the bit representing i to 1;
 * O(1) */
void ind_on(uchar* ind, int i);

/* Requires : there must be at least i bits in ind;
 * Sets the bit representing i to 0;
 * O(1) */
void ind_off(uchar* ind, int i); 

/* Deprecated */
int ind_id_min(int* t, uchar* ind, int n);

/* Warning : allocate memory;
 * Requires : there must be at least n bits in ind;
 * Returns a new array where containing the elements of t that are contained in ind;
 * O(n) */
int* ind_inter(int* input, uchar* ind, int n, int* k);

/* Requires : there must be at least n bits in ind;
 * Returns the numbers of bits equals to 1 in ind;
 * O(n) */
int ind_size(uchar* ind, int n);


void ind_print(uchar*, int n);

#endif   /* ----- #ifndef array_INC  ----- */
