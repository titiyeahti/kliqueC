/*
 * =====================================================================================
 *
 *       Filename:  avl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/02/2020 22:45:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

#include "avl.h"

int elt_compare(elt e1, elt e2)
{
				return e1.deg - e2.deg 
								|| e1.id - e2.id;
}

elt elt_create(int deg, int id)
{
				elt res;
				res.deg = deg;
				res.id = id;

				return res;
}

int avl_is_empty(avl a)
{
				return a == NULL;
}

int avl_hauteur(avl a)
{
				if (a != NULL)
								return a->h;
				else 
								return 0;
}

avl avl_node(avl g, avl d, elt e)
{
				avl res = malloc(sizeof(node));
				res->g = g;
				res->d = d;
				res->e = e;
				res->h = MAX(avl_hauteur(g), avl_hauteur(d)) + 1;

				return res;
}

/* from caml */
avl avl_balance(avl a)
{
				if (a == NULL)
								return NULL;
				else
				{
								int hg, hd;
								elt e;
								avl g, d;
								
								e = a->e;
								g = a->g;
								d = a->d;
								hg = avl_hauteur(a->g);
								hd = avl_hauteur(a->d);

								if (hg > (hd + 1))
								{
												if (g == NULL)
																exit(EXIT_FAILURE);
												else
												{
																int hgg, hgd;
																elt eg;
																avl gg, gd;

																eg = g->e;
																gg = g->g;
																gd = g->d;
																hgg = avl_hauteur(gg);
																hgd = avl_hauteur(gd);

																if (hgg > hgd)
																{
																				free(g);
																				free(a);
																				return avl_node(gg, avl_node(gd, d, e), eg);
																}
																else
																{
																				if(gd == NULL)
																								exit(EXIT_FAILURE);
																				else
																				{
																								elt egd;
																								avl gdg, gdd;

																								egd = gd->e;
																								gdg = gd->g;
																								gdd = gd->d;

																								free(gd);
																								free(g);
																								free(a);
																								return avl_node(avl_node(gg, gdg, eg),
																																avl_node(gdd, d, e),
																																egd);
																				}
																}
												}
								}
								if (hd > (hg + 1))
								{
												if (d == NULL)
																exit(EXIT_FAILURE);
												else
												{
																int hdg, hdd;
																elt ed;
																avl dg, dd;

																ed = d->e;
																dg = d->g;
																dd = d->d;
																hdg = avl_hauteur(dg);
																hdd = avl_hauteur(dd);

																if (hdg > hdd)
																{
																				free(d);
																				free(a);
																				return avl_node(avl_node(g, dg, e), dd, ed);
																}
																else
																{
																				if(dg == NULL)
																								exit(EXIT_FAILURE);
																				else
																				{
																								elt edg;
																								avl dgg, dgd;

																								edg = dg->e;
																								dgg = dg->g;
																								dgd = dg->d;

																								free(dg);
																								free(d);
																								free(a);
																								return avl_node(avl_node(g, dgg, e),
																																avl_node(dgd, dd, ed),
																																edg);
																				}
																}
												}
								}
								else 
												return a;
				}
}

avl avl_add(avl a, elt e)
{
				if(a == NULL)
								return avl_node(NULL, NULL, e);
				else
				{
								int c;
								avl g, d;
								elt e2 = a->e;
								g = a->g;
								d = a->d;

								c = elt_compare(e, e2);
								/* if the elt is already there we do not replace it*/
								if (c == 0)
												return a;
								if (c < 0)
												return avl_balance(avl_node(avl_add(g, e), d, e2));
								else
												return avl_balance(avl_node(g, avl_add(d, e), e2));
				}
}

elt avl_get_min(avl a)
{
				if (a == NULL)
								exit(EXIT_FAILURE);
				else
				{
								avl g = a->g;
								if (g == NULL)
												return a->e;
								else
												return avl_get_min(g);
				}
}

avl avl_remove(avl a, elt e)
{
				if(a == NULL)
								return NULL;
				else
				{
								int c;
								avl g, d;
								elt e2;
								e2 = a->e;
								g = a->g;
								d = a->d;

								c = elt_compare(e, e2);
								/* if the elt is already there we do not replace it*/
								if (c < 0)
												return avl_balance(avl_node(avl_remove(g, e), d, e2));
								if (c > 0)
												return avl_balance(avl_node(g, avl_remove(d, e), e2));
								else
								{
												if(d == NULL)
																return g;
												else
												{
																elt e3 = avl_get_min(d);
																
																free(a);

																return avl_balance(avl_node(g, avl_remove(d, e3), e3));
												}
								}
				}
}

/* O(nlogn) */
avl avl_construct(int* t, int n)
{
				avl res = NULL;
				int i;
				elt e;

				for(i=0; i<n; i++)
				{
								e = elt_create(t[i], i);
								res = avl_add(res, e);
				}
				return res;
}

void avl_free(avl a)
{
				if (a != NULL)
				{
								avl_free(a->g);
								avl_free(a->d);
								free(a);
				}
}

void avl_print(avl a)
{
				if (a != NULL)
				{
								avl_print(a->g);
								printf("(%d, %d) ", a->e.id, a->e.deg);
								avl_print(a->d);
				}
}
