#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

// SPOJ QTREE3: Query on a tree again!
//
// A type-0 operation flips one vertex between white and black.  A type-1
// operation asks for the black vertex nearest to root 1 on the path 1 -> v.
// Heavy-light decomposition breaks that path into O(log N) array intervals.
// A segment tree stores the shallowest black vertex in every interval.
class MinSegmentTree {
  public:
    using Candidate = pair<int, int>;  // (depth, vertex)

    explicit MinSegmentTree(int element_count) {
        size_ = 1;
        while (size_ < element_count) size_ *= 2;
        tree_.assign(2 * size_, missing());
    }

    static Candidate missing() {
        return {numeric_limits<int>::max(), -1};
    }

    // A toggle changes exactly one leaf.  Recomputing its ancestors restores
    // the minimum-depth candidate for every segment containing that vertex.
    void set_value(int index, Candidate value) {
        index += size_;
        tree_[index] = value;
        for (index /= 2; index >= 1; index /= 2) {
            tree_[index] = min(tree_[2 * index], tree_[2 * index + 1]);
        }
    }

    // Return the shallowest black vertex whose HLD position is in the closed
    // interval [left, right].  White vertices are represented by infinity.
    Candidate range_min(int left, int right) const {
        Candidate answer = missing();
        left += size_;
        right += size_;
        while (left <= right) {
            if (left & 1) answer = min(answer, tree_[left++]);
            if (!(right & 1)) answer = min(answer, tree_[right--]);
            left /= 2;
            right /= 2;
        }
        return answer;
    }

  private:
    int size_;
    vector<Candidate> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, operation_count;
    cin >> node_count >> operation_count;

    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    // Build a root-first order iteratively.  Avoiding recursive DFS matters on
    // a legal input shaped like one 100,000-vertex chain.
    vector<int> parent(node_count + 1), depth(node_count + 1);
    vector<int> order = {1};
    for (size_t index = 0; index < order.size(); ++index) {
        const int vertex = order[index];
        for (const int next : graph[vertex]) {
            if (next == parent[vertex]) continue;
            parent[next] = vertex;
            depth[next] = depth[vertex] + 1;
            order.push_back(next);
        }
    }

    // Children appear after parents in order, so reverse order computes every
    // subtree before its parent.  The largest child receives the heavy edge.
    vector<int> subtree_size(node_count + 1, 1);
    vector<int> heavy_child(node_count + 1, 0);
    for (int index = node_count - 1; index >= 0; --index) {
        const int vertex = order[index];
        int largest_child_size = 0;
        for (const int next : graph[vertex]) {
            if (parent[next] != vertex) continue;
            subtree_size[vertex] += subtree_size[next];
            if (subtree_size[next] > largest_child_size) {
                largest_child_size = subtree_size[next];
                heavy_child[vertex] = next;
            }
        }
    }

    vector<int> chain_head(node_count + 1), position(node_count + 1);
    int next_position = 0;
    vector<pair<int, int>> pending_chains = {{1, 1}};

    // Each heavy chain is written consecutively from its shallowest vertex to
    // its deepest.  Every light child begins a separate pending chain.
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

    MinSegmentTree segment_tree(node_count);
    vector<bool> is_black(node_count + 1, false);

    const auto root_path_answer = [&](int vertex) {
        MinSegmentTree::Candidate answer = MinSegmentTree::missing();

        // The unprocessed path is always root 1 through vertex.  Query the
        // current chain prefix, then jump over the light edge above its head.
        while (chain_head[vertex] != chain_head[1]) {
            answer = min(answer, segment_tree.range_min(
                                     position[chain_head[vertex]],
                                     position[vertex]));
            vertex = parent[chain_head[vertex]];
        }

        // Root and the remaining endpoint now share one final heavy chain.
        answer = min(answer,
                     segment_tree.range_min(position[1], position[vertex]));
        return answer.second;
    };

    while (operation_count--) {
        int type, vertex;
        cin >> type >> vertex;
        if (type == 0) {
            is_black[vertex] = !is_black[vertex];
            const auto value = is_black[vertex]
                                   ? MinSegmentTree::Candidate{depth[vertex], vertex}
                                   : MinSegmentTree::missing();
            segment_tree.set_value(position[vertex], value);
        } else {
            cout << root_path_answer(vertex) << '\n';
        }
    }
    return 0;
}
