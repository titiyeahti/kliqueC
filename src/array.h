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

/* O(n) */
void print(int* t, int n);

/* O(nlogn) */
void quicksort(int* t, int n);

/* O(n) */
int contains(int* t, int i, int n);

/* Malloc *
 * O(n1+n2) */
int* inter(int* t1, int* t2, int n1, int n2, int* k);

/* Malloc 
 * 1) the last elt t1 of must be less than the first of t2 
 * 2) the size of the returned array is n1+n2 
 * 3) depending on memcpy, O(n1+n2) or O(1) */
int* concat(int* t1, int* t2, int n1, int n2);

/* indicator function */
/* no protection nor size of the indicator function since it will 
 * always be of size n (the number of vertices) and every int we consider 
 * is less than n */

/* O(n) */
int ind_id_min(int* t, uchar* ind, int n);

/* O(1) */
int ind_contains(uchar* ind, int i);

/* O(1) */
void ind_on(uchar* ind, int i);

/* O(1) */
void ind_off(uchar* ind, int i); 

/* Malloc */
/* O(n) */
int* ind_inter(int* input, uchar* ind, int n, int* k);

/* O(n) */
int ind_size(uchar* ind, int n);

#endif   /* ----- #ifndef array_INC  ----- */
