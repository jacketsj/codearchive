## Code Archive

This is a archive of various common data structures, algorithms, and other things. Re-implementation isn't very fun.
Implementation is oriented primarily towards competitive programming, so you won't see templating or OO in use here, although all implementations should be adaptable.

Things are categorized into folders, and all tied code is placed into a single sourcecode file (for easy access, compilation, and testing).
For example, Kruskal's algorithm and uptrees are in the same file.

### A (Quickly Outdated) List of Categories and Code:
* Arrays:
	* Binary search (genericized) - can allow for any valid functional input
	* Counting sort - implemented to allow arbitrary values in input array, but runtime will depend on the range.
	* Comparison sorts - Mergesort (stable), Quicksort (in-place)
* Geometry:
	* Line intersection
	* Convex hull - Both gift wrapping (*O(nh)*) and Graham Scan (*O(nlog n)*)
* Graphs:
	* Max flow - Relabel-to-front implementation (*O(n^3)*)
	* BFS/DFS/Dijkstra/Toposort - Standard with arbitrary visit functions
* Numeric:
	* Euclidean algorithm(s) - GCD, LCM, modular inverse
	* Sieve of Eratosthenes - all prime numbers less than or equal to *n*
* Strings:
	* Matching - Tries and Knuth-Morris-Pratt (with arbitrary alphabet size for the latter)
* Trees:
	* Balanced trees - AVL Tree


### Unsorted List of (Eventual) Planned Code:
* Balanced trees: Treaps, Splay trees
* Indexing trees: BITs, Segtrees, Quadtrees, general k-d trees
* More sorts: Heapsort, Bucket sort, Radix sort
* Big integers
* More geometry: Nearest pair, line sweep, online convex hull + convex layers (with Overmars and van Leeuwen)
* SQRT decomposition
* Linear algebra (and programming): Simplex algorithm, (fast) matrix exponentiation/multiplication
* FFT and common uses
* Graphs: Floyd-Warshall, SPFA, BCC, SCC, 2-SAT
* Flow applications/reductions: Mutli sink/source, node capacity, bipartite matching, scheduling
