/*
 * =====================================================================================
 *
 *       Filename:  avl.h
 *
 *    Description:  The heap was not a good idea so I give a try to AVL
 *
 *        Version:  1.0
 *        Created:  19/02/2020 22:28:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */


#ifndef  avl_INC
#define  avl_INC

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

typedef struct elt 
{
				int deg;
				int id;
} elt;


typedef struct node
{
				elt e;
				struct node * g;
				struct node * d;
				int h;
} node;

typedef node* avl;

/* e1.deg - e2.deg || e1.id - e2.id */
int elt_compare(elt e1, elt e2);

elt elt_create(int deg, int id);

int avl_is_empty(avl a);

int avl_hauteur(avl a);

avl avl_node(avl g, avl d, elt e);

avl avl_balance(avl a);

avl avl_add(avl a, elt e);

avl avl_construct(int* t, int n);

avl avl_remove(avl a, elt e);

elt avl_get_min(avl a);

/* do pop by e = get_min then remove e */
/* elt avl_pop_min(alv a, elt e);
 */

void avl_free(avl a);

void avl_print(avl a);

#endif   /* ----- #ifndef avl_INC  ----- */
