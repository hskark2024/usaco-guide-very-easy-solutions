#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// A Fenwick tree stores prefix sums while supporting point changes.
// Both operations touch only O(log N) carefully chosen array positions.
class FenwickTree {
   public:
	// Fenwick indices start at 1, so allocate one extra position.
	explicit FenwickTree(int size) : tree(size + 1, 0) {}

	// Add delta to one flattened-tree position.
	void add(int index, long long delta) {
		// Convert the zero-based Euler index to a one-based Fenwick index.
		for (++index; index < static_cast<int>(tree.size()); index += index & -index) {
			tree[index] += delta;
		}
	}

	// Return the sum over the half-open interval [0, end).
	long long prefix_sum(int end) const {
		long long result = 0;
		for (; end > 0; end -= end & -end) {
			result += tree[end];
		}
		return result;
	}

	// Return the sum over the half-open interval [left, right).
	long long range_sum(int left, int right) const {
		return prefix_sum(right) - prefix_sum(left);
	}

   private:
	vector<long long> tree;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int node_count, query_count;
	cin >> node_count >> query_count;

	// Values and all subtree sums can exceed 32-bit int: N and each value
	// can both be as large as 200,000 and 1,000,000,000 respectively.
	vector<long long> value(node_count);
	for (long long &current_value : value) {
		cin >> current_value;
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

	// Flatten the rooted tree in preorder. Every subtree becomes one
	// contiguous half-open segment [entry[v], exit[v]).
	vector<int> parent(node_count, -1);
	vector<int> entry(node_count);
	vector<int> exit(node_count);
	vector<int> euler_order;
	euler_order.reserve(node_count);

	// The stack stores (vertex, state). State 0 enters a vertex; state 1
	// exits it. This simulates recursive DFS without risking stack overflow
	// on a path with 200,000 vertices.
	vector<pair<int, int>> stack;
	stack.push_back({0, 0});
	while (!stack.empty()) {
		auto [vertex, state] = stack.back();
		stack.pop_back();

		if (state == 0) {
			entry[vertex] = static_cast<int>(euler_order.size());
			euler_order.push_back(vertex);

			// Schedule the exit after every child has been processed.
			stack.push_back({vertex, 1});
			for (auto it = graph[vertex].rbegin(); it != graph[vertex].rend(); ++it) {
				const int child = *it;
				if (child == parent[vertex]) {
					continue;
				}
				parent[child] = vertex;
				stack.push_back({child, 0});
			}
		} else {
			// At exit time, every descendant has already entered the tour.
			exit[vertex] = static_cast<int>(euler_order.size());
		}
	}

	FenwickTree fenwick(node_count);
	for (int vertex = 0; vertex < node_count; ++vertex) {
		fenwick.add(entry[vertex], value[vertex]);
	}

	for (int query = 0; query < query_count; ++query) {
		int type, vertex;
		cin >> type >> vertex;
		--vertex;

		if (type == 1) {
			long long new_value;
			cin >> new_value;

			// Fenwick updates are additive, so apply only the difference.
			fenwick.add(entry[vertex], new_value - value[vertex]);
			value[vertex] = new_value;
		} else {
			// Euler flattening turns this tree query into one range sum.
			cout << fenwick.range_sum(entry[vertex], exit[vertex]) << '\n';
		}
	}
}
