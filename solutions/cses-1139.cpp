#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// Fenwick tree for point additions and prefix/range sums.
class FenwickTree {
   public:
	explicit FenwickTree(int size) : tree(size + 1, 0) {}

	void add(int index, int delta) {
		for (++index; index < static_cast<int>(tree.size()); index += index & -index) {
			tree[index] += delta;
		}
	}

	int prefix_sum(int end) const {
		int result = 0;
		for (; end > 0; end -= end & -end) {
			result += tree[end];
		}
		return result;
	}

	int range_sum(int left, int right) const {
		return prefix_sum(right) - prefix_sum(left);
	}

   private:
	vector<int> tree;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int node_count;
	cin >> node_count;

	vector<int> color(node_count);
	for (int &current_color : color) {
		cin >> current_color;
	}

	vector<vector<int>> graph(node_count);
	for (int edge = 0; edge < node_count - 1; ++edge) {
		int first, second;
		cin >> first >> second;
		--first;
		--second;
		graph[first].push_back(second);
		graph[second].push_back(first);
	}

	// A preorder Euler tour places every vertex's entire subtree into one
	// contiguous segment [entry[v], exit[v]).
	vector<int> parent(node_count, -1);
	vector<int> entry(node_count);
	vector<int> exit(node_count);
	vector<int> euler_order;
	euler_order.reserve(node_count);

	// Use explicit enter/exit events instead of recursive DFS. CSES allows a
	// chain of 200,000 vertices, which can overflow the process call stack.
	vector<pair<int, int>> stack = {{0, 0}};
	while (!stack.empty()) {
		auto [vertex, state] = stack.back();
		stack.pop_back();

		if (state == 0) {
			entry[vertex] = static_cast<int>(euler_order.size());
			euler_order.push_back(vertex);
			stack.push_back({vertex, 1});

			// Reverse iteration preserves the adjacency-list order in the tour;
			// correctness does not depend on which child is visited first.
			for (auto it = graph[vertex].rbegin(); it != graph[vertex].rend(); ++it) {
				const int child = *it;
				if (child == parent[vertex]) {
					continue;
				}
				parent[child] = vertex;
				stack.push_back({child, 0});
			}
		} else {
			exit[vertex] = static_cast<int>(euler_order.size());
		}
	}

	vector<int> answer(node_count);
	FenwickTree fenwick(node_count);

	// last_position[color] is the closest occurrence strictly to the right
	// of the current Euler index. unordered_map supports color values up to 1e9.
	unordered_map<int, int> last_position;
	last_position.reserve(static_cast<size_t>(node_count) * 2);

	// Scan right to left. For each color, exactly its leftmost occurrence in
	// the current suffix is marked 1. Therefore a range sum counts colors,
	// not vertices, once the scan reaches that range's left endpoint.
	for (int index = node_count - 1; index >= 0; --index) {
		const int vertex = euler_order[index];
		const int current_color = color[vertex];

		auto previous = last_position.find(current_color);
		if (previous != last_position.end()) {
			// The newer leftmost occurrence replaces the old representative.
			fenwick.add(previous->second, -1);
		}
		fenwick.add(index, 1);
		last_position[current_color] = index;

		// This index is entry[vertex], so the vertex's whole subtree segment
		// is ready to query now.
		answer[vertex] = fenwick.range_sum(entry[vertex], exit[vertex]);
	}

	for (int vertex = 0; vertex < node_count; ++vertex) {
		cout << answer[vertex] << (vertex + 1 == node_count ? '\n' : ' ');
	}
}
