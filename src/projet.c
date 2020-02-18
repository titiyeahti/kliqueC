/*
 * =====================================================================================
 *
 *       Filename:  projet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/02/2020 23:48:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */


void listing(graph_p g, int* sg, int* clique, int size, int k, int ck,
							 int to_free, int* deg)
{
				int i, j;
				int new_size, n2;
				int cur, tf;
				int* neigh;
				int* nsg;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								for(i=0; i < size; i++)
												deg[sg[i]] ++;
								
								for(j=0; j<ck-1; j++)
												deg[clique[j]] += size;
				}
				else 
				{
								for(i=0; i<size; i++)
								{
												if (k != ck)
																cur = sg[i];
												else 
																cur = i;

												neigh = g->edges + g->vertices[cur];
												n2 = g->vertices[cur+1] - 
																g->vertices[cur];

												clique[ck-k] = cur;

												if(k != ck)
												{
																nsg = inter(sg, neigh, size, n2, &new_size);
																tf = 1;
												}
												else
												{
																nsg = neigh;
																new_size = n2;
																tf = 0;
												}
												
												
												if(new_size > 0)
																listing(g, nsg, clique, new_size, k-1, 
																								ck, tf, deg);
								}
				}
				
				if (to_free)
								free(sg);
}

void remove_listing(graph_p g, int* sg, int* clique, int size, int k, 
								int ck, int target, int* deg)
{
				int i;
				int j;
				int flag = 0;

				/* my graph representation is such that stop at k==2 is a pain */
				if (k==1)
				{
								for(j=0; j<size; j++)
								{
												if(sg[j] == target)
												{
																flag = 1;
																break;
												}
								}

								for(j=0; j<ck-1; j++)
								{
												if(clique[j] == target)
												{
																flag = 2;
																break;
												}
								}

								if (flag)
								{
												/* target is in clique */
												if(flag == 2)
												{
																for(i=0; i < size; i++)
																				deg[sg[i]] --;
																
																for(j=0; j<ck-1; j++)
																				deg[clique[j]] -= (size);
												}
												/* target is not in clique */
												else 
												{
																deg[target] --;
																for(j=0; j<ck-1; j++)
																				deg[clique[j]] --;
												}
								}
				}
				else 
				{
								for(i=0; i<size; i++)
								{
												int cur = sg[i];
												int* neigh = g->edges + g->vertices[cur];
												int n2 = g->vertices[cur+1] - 
																g->vertices[cur];
												int new_size;
												int* nsg = inter(sg, neigh, size, n2, &new_size);
												clique[ck-k] = cur;

												for(j=0; j<new_size; j++)
												{
																if(nsg[j] == target)
																{
																				flag = 1;
																				break;
																}
												}

												for(j=0; j< ck+1-k; j++)
												{
																if(clique[j] == target)
																{
																				flag = 1;
																				break;
																}
												}
												
												if((new_size > 0) && (flag))
																remove_listing(g, nsg, clique, new_size, k-1, 
																								ck, target, deg);
								}
				}

				free(sg);
}

int* kdeg(graph_p g, int k)
{
				int* deg = malloc(g->n*sizeof(int));
				int clique[k];
				int i;

				for(i=0; i<k; i++)
								clique[i] = -1;

				listing(g, NULL, clique, g->n, k, k, 0, deg);

				return deg; 
}

/* here ind is and indicator function */
double clique_density(graph_p g, int* ind)
{
				int i, j;
				int n, m;
				int start, stop;
				int dest;
				double res;

				n = 0;
				m = 0;

				for(i=0; i<g->n; i++)
				{
								if(ind[i])
								{
												n++;
												
												start = g->vertices[i];
												stop = g->vertices[i+1];

												for(j=start; j<stop; j++)
												{
																dest = g->edges[j];

																if(ind[dest])
																				m++;
												}
								}
				}

				res = (double) 2.*m / ((double)(n-1)*(double)n);
				if (res < 0.)
								printf("(n, m) = (%d, %d) clique_density = %f\n", 
																n, m, res);

				return res;
}

int* quasi_clique(graph_p g, int s, int k)
{
				clock_t t1;
				int* deg;
				int* neigh;
				int* sg;
				int i, j, l, id;
				int size, size2;
				int ind[g->n];
				int* ind_b;
				double density, density_b;
				int clique[k];

				ind_b = malloc(g->n*sizeof(int));

				for(i=0; i<g->n; i++)
				{
								ind[i] = 1;
								ind_b[i] = 1;
				}

				density = clique_density(g, ind);
				density_b = density;

				t1 = clock();
				deg = kdeg(g, k);
				t1 = clock() - t1;

				printf("kdeg time : %f\n", (float)t1/CLOCKS_PER_SEC);

				/*-----------------------------------------------------------------------------
				 *  SAFE : You can trust the code below.
				 *-----------------------------------------------------------------------------*/

				for(i=g->n; i>s; i--)
				{
								/* la */
								id = ind_id_min(deg, ind, g->n);

								t1 = clock();
								/* removing cliques */
								for(j=0; j<id+1; j++)
								{
												if(ind[j])
												{
																clique[0] = j;
																size = g->vertices[j+1] - g->vertices[j];
																neigh = g->edges + g->vertices[j];

																sg = ind_inter(neigh, ind, size, &size2);

																int flag = (id == j);
																for(l=0; l<size2; l++)
																{
																				if(flag || neigh[l] == id)
																				{
																								flag = 1;
																								break;
																				}
																}
																
																if (flag)
																				remove_listing(g, sg, clique, size2, k-1, k, id, deg);
												}

								}
								
								t1 = clock() - t1;

								ind[id] = 0;

								/* adjusting clique density */
								density = clique_density(g, ind);
								
/* 								printf("id = %d : %f, %f\n", id, (float)t1/CLOCKS_PER_SEC, density);
 */

								/* update the best */
								if(density > density_b)
								{
												memcpy(ind_b, ind, g->n*sizeof(int));
												density_b = density;
												
												if (density == 1.)
																break;
								}
				}
				return ind_b;
}
