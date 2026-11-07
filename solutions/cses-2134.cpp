#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// CSES 2134: Path Queries II
//
// Heavy-light decomposition turns any tree path into O(log N) contiguous
// ranges.  An iterative segment tree stores the maximum value in each range,
// giving O(log^2 N) path queries and O(log N) point updates.
class MaxSegmentTree {
  public:
    explicit MaxSegmentTree(int element_count) {
        size_ = 1;
        while (size_ < element_count) size_ *= 2;
        tree_.assign(2 * size_, 0);
    }

    void set_value(int index, int value) {
        index += size_;
        tree_[index] = value;
        for (index /= 2; index >= 1; index /= 2) {
            tree_[index] = max(tree_[2 * index], tree_[2 * index + 1]);
        }
    }

    int range_max(int left, int right) const {
        int answer = 0;  // Official node values are positive.
        left += size_;
        right += size_;
        while (left <= right) {
            if (left & 1) answer = max(answer, tree_[left++]);
            if (!(right & 1)) answer = max(answer, tree_[right--]);
            left /= 2;
            right /= 2;
        }
        return answer;
    }

  private:
    int size_;
    vector<int> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, query_count;
    cin >> node_count >> query_count;

    vector<int> value(node_count + 1);
    for (int vertex = 1; vertex <= node_count; ++vertex) cin >> value[vertex];

    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    vector<int> parent(node_count + 1), depth(node_count + 1);
    vector<int> order = {1};
    parent[1] = 0;
    for (size_t index = 0; index < order.size(); ++index) {
        const int vertex = order[index];
        for (const int next : graph[vertex]) {
            if (next == parent[vertex]) continue;
            parent[next] = vertex;
            depth[next] = depth[vertex] + 1;
            order.push_back(next);
        }
    }

    // Process children before parents to find subtree sizes and each vertex's
    // largest child.  Following largest-child edges creates the heavy chains.
    vector<int> subtree_size(node_count + 1, 1), heavy_child(node_count + 1, 0);
    for (int index = node_count - 1; index >= 0; --index) {
        const int vertex = order[index];
        int largest_size = 0;
        for (const int next : graph[vertex]) {
            if (parent[next] != vertex) continue;
            subtree_size[vertex] += subtree_size[next];
            if (subtree_size[next] > largest_size) {
                largest_size = subtree_size[next];
                heavy_child[vertex] = next;
            }
        }
    }

    vector<int> chain_head(node_count + 1), position(node_count + 1);
    int next_position = 0;
    vector<pair<int, int>> pending_chains = {{1, 1}};

    // Walk each heavy chain in one loop, assigning consecutive positions.
    // Light children start new chains and are saved for later processing.
    while (!pending_chains.empty()) {
        const auto [start, head] = pending_chains.back();
        pending_chains.pop_back();
        for (int vertex = start; vertex != 0; vertex = heavy_child[vertex]) {
            chain_head[vertex] = head;
            position[vertex] = next_position++;
            for (const int next : graph[vertex]) {
                if (parent[next] == vertex && next != heavy_child[vertex]) {
                    pending_chains.push_back({next, next});
                }
            }
        }
    }

    MaxSegmentTree segment_tree(node_count);
    for (int vertex = 1; vertex <= node_count; ++vertex) {
        segment_tree.set_value(position[vertex], value[vertex]);
    }

    const auto path_max = [&](int first, int second) {
        int answer = 0;
        // Remove one whole chain suffix from the deeper side each iteration.
        // A root-to-leaf path crosses at most O(log N) light edges.
        while (chain_head[first] != chain_head[second]) {
            if (depth[chain_head[first]] < depth[chain_head[second]]) {
                swap(first, second);
            }
            answer = max(answer, segment_tree.range_max(
                                     position[chain_head[first]], position[first]));
            first = parent[chain_head[first]];
        }

        if (depth[first] > depth[second]) swap(first, second);
        return max(answer,
                   segment_tree.range_max(position[first], position[second]));
    };

    bool printed_answer = false;
    while (query_count--) {
        int type, first, second;
        cin >> type >> first >> second;
        if (type == 1) {
            value[first] = second;
            segment_tree.set_value(position[first], second);
        } else {
            if (printed_answer) cout << ' ';
            cout << path_max(first, second);
            printed_answer = true;
        }
    }
    cout << '\n';
    return 0;
}
