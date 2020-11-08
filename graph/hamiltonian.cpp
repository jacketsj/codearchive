#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> graph;

bool has_hamiltonian_cycle(const graph& g, int start_node, int current_node,
													 vector<bool>& current_stack, int remaining,
													 bool print) {
	if (current_stack[current_node]) {
		if (remaining == 0 && start_node == current_node) {
			if (print)
				cout << "YES" << '\n';
			return true;
		}
		return false;
	}

	current_stack[current_node] = true;

	for (auto next_node : g[current_node]) {
		if (has_hamiltonian_cycle(g, start_node, next_node, current_stack,
															remaining - 1, print)) {
			if (print)
				cout << current_node << ' ';
			return true;
		}
	}

	current_stack[current_node] = false;
	return false;
}

bool has_hamiltonian_cycle(const graph& g, bool print = false) {
	int start_node = 0;
	vector<bool> current(g.size());
	if (has_hamiltonian_cycle(g, start_node, start_node, current, g.size(),
														print)) {
		return true;
	}
	if (print)
		cout << "NO\n";
	return false;
}

bool has_hamiltonian_cycle_with_edges(
		const graph& g, const vector<pair<int, int>>& required_edges) {
	graph g2 = g;
	int extra_edge_no = g.size();
	for (auto [v1, v2] : required_edges) {
		int mid = extra_edge_no++;
		g2.push_back(vector<int>({v1, v2})); // add a new auxillary vertex
		// move the edge v1->v2 to be v1->mid->v2
		for (auto& v2_poss_ref : g2[v1]) {
			if (v2_poss_ref == v2) {
				v2_poss_ref = mid;
				break;
			}
		}
		// move the edge v2->v1 to be v2->mid->v1
		for (auto& v1_poss_ref : g2[v2]) {
			if (v1_poss_ref == v1) {
				v1_poss_ref = mid;
				break;
			}
		}
	}
	return has_hamiltonian_cycle(g2);
}

void tests() {
	cout << "Running tests\n";
	graph g_triangle = {{1, 2}, {2, 0}, {0, 1}};
	cout << "Triangle: Has Hamiltonian Cycle? "
			 << has_hamiltonian_cycle(g_triangle) << endl;
	graph g_quad = {{1, 3}, {2, 0}, {1, 3}, {2, 0}};
	cout << "Quad: Has Hamiltonian Cycle? " << has_hamiltonian_cycle(g_quad)
			 << endl;
	graph g_line = {{1}, {0}};
	cout << "Line: Has Hamiltonian Cycle? " << has_hamiltonian_cycle(g_line)
			 << " This one breaks convention. That's ok." << endl;
	graph g_line_2 = {{1}, {0, 2}, {1}};
	cout << "Line (length-2): Has Hamiltonian Cycle? "
			 << has_hamiltonian_cycle(g_line_2) << endl;

	graph g_cube = {{1, 2, 6}, {0, 4, 7}, {0, 3, 4}, {2, 5, 6},
									{1, 2, 5}, {4, 3, 7}, {3, 0, 7}, {6, 1, 5}};
	cout << "Cube: Has Hamiltonian Cycle? " << has_hamiltonian_cycle(g_cube)
			 << endl;
	vector<pair<int, int>> g_cube_specified_edges = {
			{0, 1}, {4, 5}, {2, 3}, {6, 7}};
	cout << "Cube: Has Hamiltonian Cycle using 4 specific edges? "
			 << has_hamiltonian_cycle_with_edges(g_cube, g_cube_specified_edges)
			 << endl;
	vector<pair<int, int>> g_cube_specified_edges_bad = {
			{0, 1}, {4, 5}, {2, 3}, {6, 7}, {0, 6}, {1, 7}, {2, 4}, {3, 5}};
	cout << "Cube: Has Hamiltonian Cycle using 8 specific edges (impossible)? "
			 << has_hamiltonian_cycle_with_edges(g_cube, g_cube_specified_edges_bad)
			 << endl;

	cout << '\n';

	graph g_B = {{15, 1, 5},	{0, 4, 2},		{1, 3, 17},		{2, 4, 6},
							 {1, 3, 5},		{4, 0, 8},		{3, 7, 8},		{6, 8, 16},
							 {7, 5, 11},	{6, 10, 12},	{9, 11, 13},	{8, 10, 14},
							 {9, 13, 15}, {12, 10, 14}, {13, 11, 17}, {12, 0, 16},
							 {15, 7, 17}, {16, 14, 2}};
	vector<pair<int, int>> g_B_specified_edges = {{1, 4}, {13, 10}};
	cout << "B: Has Hamiltonian Cycle? " << has_hamiltonian_cycle(g_B) << endl;
	cout << "B: Has Hamiltonian Cycle using both specified edges? "
			 << has_hamiltonian_cycle_with_edges(g_B, g_B_specified_edges) << endl;
	cout << "B: Has Hamiltonian Cycle using one specified edge? "
			 << has_hamiltonian_cycle_with_edges(g_B,
																					 vector({g_B_specified_edges[0]}))
			 << endl;
	cout << "B: Has Hamiltonian Cycle using one specified edge (the other one)? "
			 << has_hamiltonian_cycle_with_edges(g_B,
																					 vector({g_B_specified_edges[1]}))
			 << endl;
}

int main() { tests(); }
