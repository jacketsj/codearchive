This is a archive of various common data structures, algorithms, and other things. Re-implementation isn't very fun.


Things are categorized into folders, and all tied code is placed into a single sourcecode file (for easy access, compilation, and testing).
For example, Kruskal's algorithm and uptrees are in the same file.

A (quickly outdated) list of categories and code is as follows:
* Arrays:
	* Binary search (genericized) - can allow for any valid functional input
	* Counting sort - implemented to allow arbitrary values in input array, but runtime will depend on the range.
* Geometry:
	* Line intersection
	* Convex hull - Both gift wrapping (*O(nh)*) and Graham Scan (*O(nlog n)*)
* Graphs:
	* Max flow - Relabel-to-front implementation (*O(n^3)*)
	* BFS/DFS/Dijkstra/Toposort - Standard with arbitrary visit functions
* Numeric:
	* Euclidean algorithm(s) - GCD, LCM, modular inverse
	* Sieve of Eratosthenes - all prime numbers less than or equal to *n*


Unsorted list of (eventual) planned code:
* Balanced trees: Treaps, AVL trees, Splay trees
* Indexing trees: BITs, Segtrees, Quadtrees, general k-d trees
* More sorts: Mergesort, Heapsort, Quicksort, Bucket sort, Radix sort
* Big integers
* More geometry: Nearest pair, line sweep, online convex hull (with Overmars and van Leeuwen)
* SQRT decomposition
