#include <iostream>
#include <vector>
using namespace std;

// USACO Gold 2019 February: Cow Land
//
// Heavy-light decomposition splits a route into O(log N) array intervals.  A
// segment tree stores XOR on those intervals, supporting point assignments and
// route XOR queries in O(log N) and O(log^2 N), respectively.
class XorSegmentTree {
  public:
    explicit XorSegmentTree(int element_count) {
        size_ = 1;
        while (size_ < element_count) size_ *= 2;
        tree_.assign(2 * size_, 0);
    }

    void set_value(int index, int value) {
        index += size_;
        tree_[index] = value;
        for (index /= 2; index >= 1; index /= 2) {
            tree_[index] = tree_[2 * index] ^ tree_[2 * index + 1];
        }
    }

    int range_xor(int left, int right) const {
        int answer = 0;
        left += size_;
        right += size_;
        while (left <= right) {
            if (left & 1) answer ^= tree_[left++];
            if (!(right & 1)) answer ^= tree_[right--];
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

    vector<int> enjoyment(node_count + 1);
    for (int vertex = 1; vertex <= node_count; ++vertex) cin >> enjoyment[vertex];

    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    // Build the rooted tree iteratively so a worst-case chain never risks a
    // recursive stack overflow at the official maximum of 100,000 vertices.
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
    vector<pair<int, int>> pending_chains = {{1, 1}};
    int next_position = 0;
    while (!pending_chains.empty()) {
        const auto [start, head] = pending_chains.back();
        pending_chains.pop_back();
        for (int vertex = start; vertex; vertex = heavy_child[vertex]) {
            chain_head[vertex] = head;
            position[vertex] = next_position++;
            for (const int next : graph[vertex]) {
                if (parent[next] == vertex && next != heavy_child[vertex]) {
                    pending_chains.push_back({next, next});
                }
            }
        }
    }

    XorSegmentTree segment_tree(node_count);
    for (int vertex = 1; vertex <= node_count; ++vertex) {
        segment_tree.set_value(position[vertex], enjoyment[vertex]);
    }

    const auto path_xor = [&](int first, int second) {
        int answer = 0;
        while (chain_head[first] != chain_head[second]) {
            if (depth[chain_head[first]] < depth[chain_head[second]]) {
                swap(first, second);
            }
            answer ^= segment_tree.range_xor(position[chain_head[first]],
                                             position[first]);
            first = parent[chain_head[first]];
        }
        if (depth[first] > depth[second]) swap(first, second);
        answer ^= segment_tree.range_xor(position[first], position[second]);
        return answer;
    };

    while (query_count--) {
        int type, first, second;
        cin >> type >> first >> second;
        if (type == 1) {
            enjoyment[first] = second;
            segment_tree.set_value(position[first], second);
        } else {
            cout << path_xor(first, second) << '\n';
        }
    }
    return 0;
}
