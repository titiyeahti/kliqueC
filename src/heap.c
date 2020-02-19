/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/02/2020 16:08:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut MILHAUD (), thibaut.milhaud@ensiie.fr
 *   Organization:  ENSIIE - SUAI
 *
 * =====================================================================================
 */

int heap_size(heap_p h)
{
				return h->n;
}

/* 1 if i>j
 * 0 if i=j
 * -1 if j> i */
int compare(heap_p h, int i, int j)
{
				if (h->key[i] > h->key[j])
								return 1;
				if (h->key[i] < h->key[j])
								return -1;
				
				/* keys are equals */
				if(h->val[i] > h->val[j])
								return 1;
				if(h->val[i] < h->val[j])
								return -1;

				return 0;
}

void heap_swap(heap_p h, int i, int j)
{
				int temp;

				temp = h->key[i];
				h->key[i] = h->key[j];
				h->key[j] = temp;
				temp = h->val[i];
				h->val[i] = h->val[j];
				h->val[j] = temp;
}

/* we want to return i if key[j]<key[i] or (key[j] = key[i] and val[i] >= val[j]) */
/* return j -> we do not swap */
int arg_max(heap_p h, int i, int j)
{
				int b = compare(h, i, j);

				if (b >= 0)
								return i;
				else 
								return j;
}

/* we want to return i if key[j]>key[i] or (key[j] = key[i] and val[i] <= val[j]) */
/* return j -> we do not swap */
int arg_min(heap_p h, int i, int j)
{
				int b = compare(h i, j);

				if (b <= 0)
								return i;
				else 
								return j;
}

void heap_downtamp(heap_p h, int i)
{
				int nb = 0;
				int id;
				if(2*i+1 < h->n)
								nb ++;
				if(2*i+2 < h->n)
								nb ++;

				if (nb)
				{
								if (nb == 2)
								{
												id = arg_min(key, 2*i+1, 2*i+2);
												id = arg_min(key, i, id);
								}
								else 
								{
												id = arg_min(key, i, 2*i+1);
								}

								if (id != i)
								{
												heap_swap(h, i, id);
												heap_downtamp(h, id);
								}
				}
}

void heap_uptamp(heap_p h, int i)
{
				if (i > 0)
				{
								int id;
								id = arg_max(key, i, (i-1)/2);

								if (id != i)
								{
												heap_swap(h, i, id);
												heap_upamp(h, id);
								}
				}
}

void heap_add(heap_p h, int val, int key)
{
				h->val[h->n] = val;
				h->key[h->n] = key;

				h->n ++;
				heap_uptamp(h, (h->n)-1);
}

heap_p heap_construct(int* deg, int n)
{
				int i;
				heap_p res = malloc(sizeof(heap));

				res->n = n;

				res->val = malloc(n*sizeof(int));
				for(i=0; i<n; i++)
								res->val[i] = i;

				res->key = malloc(n*sizeof(int));
				memcpy(res->key, deg, n*sizeof(int));

				for(i = (n/2); i>=0; i--)
				{
								downtamp(h, i);
				}

				return res;
}

int heap_minval(heap_p h)
{
				return h->val[0];
}

int heap_pop(heap_p h)
{
				int val = h->val[0];
				h->n --;
				heap_swap(0, h->n);

				heap_downtamp(h, 0);
}

/* need avl to be abble to decrease key in logn */
void heap_decrease_key(heap_p, int key, int val, int k)
{

}
