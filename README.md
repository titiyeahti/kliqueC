#Example 
g : 
1->2
2->3
2->4
3->1
3->4
4->1

listing(3,g,[])

4 != 2
for u=1; u<=4; u++
g[delta\_g(u)]
listing(2, [2], [1])-> no edge left in this graph

listing(2, [3,4], [2])-> [2,3,4]

listing(2, [1,4], [3])-> [1,3,4]

listing(2, [1], [4])-> no edge left 

implementation for sets of nodes :
lists
	+ add O(1);
	+ space O(size);
	- access and remove O(size);
indicator function 
	+ access, update in O(1);
	- space O(|V(G)|);
AVL
	+ space O(size);
	+ everythingelse O(log(size))

cost :
	(in fact it is enough to compute the set of vertices o the induced graph) 
	- AVL, l>2, (fold O(n))\*(g[delta\_g(u)] (\sum i=0, i\<deg(u) log(i)) + )


convention : in the following we try to work with pointers to structs and to do 
as many operations in place.

need : 
	- 1) int list (cliques, mutable graph) (ilist = \*\*elt)
		- ilist new(int elt);
		- ilist copy(ilist l);
		- void add(ilist l, int elt);
		- bool contains(ilist l, int elt);
		- void remove(list l, int elt); while (l!= NULL) l = remove(l->elt) 
		- void free(list l); (recursive)
		- void print(l);
	- 5) int list list 
		- llist new(ilist elt);
		- void add(llist l, ilist elt);
		- void concat(llist l1, llist l2) (l1 <- l1@l2);
		- int* nb_occ(int max, llist l);
		- void free(llist l);
		- void print(l);
	- 2) mutgraph (temp structure to read the input file : int n, (ilist, nb voisins) \*)
		- mutgraph new(int size);
		- void resize(mutgraph g, int size); (only increase size)
		- void new_edge(mutgraph g, int i, int j);
		- void remove_edge(mutgraph g, int i, int j); 
		- mutgraph from_file(FILE\* file, bool directed, char weigth);
		- void free(mutgraph g);
		- void print(g);
	- 3) graph (int\* vertices, int\* edges) (re-use code from russia)
		- graph from_mutgraph(mutgraph g);
		- void sort_edges(graph g); (in place, with quick sort (code from last time));
		- void print(g);
		- void free(g);
	- 4) sortedarray \*(int n, int\* elts) to implement sets probably not a structure
				just a pointer to an array with size somewhere.
		- sortedarray new(void);
		- sortedarray copy(sortedarray a);
		- int contains(int elt);
		- void insert(int elt); (do nothing if a contains elt)
		- void remove(int elt); (removes the corresponding elt if it exists)
		- sortedarray intersection(sortedarray a, sortedarray b); (not really);
		- void free(sortedarray a);
		- void print(a);

dependencies :
	- sortedarray : -
	- ilist : -
		- llist : ilist
		- mutgraph : ilist
			- graph : mutgraph (ilist)
				- algo : graph (mutgraph (ilist)), sortedarray
				
tests :
	- everything exept algo 
	- compare result of seq algo and result of parallel one
