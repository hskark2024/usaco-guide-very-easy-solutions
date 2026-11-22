#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// BOI 2020 / Codeforces 1387B2: Village (Maximum)
//
// For an edge that separates s vertices from N-s vertices, at most
// 2 * min(s, N-s) villagers can cross that edge: the same number must cross
// in each direction.  A centroid makes every rooted subtree contain at most
// floor(N/2) vertices.  If we put a centroid-rooted DFS order on a circle and
// send every vertex floor(N/2) positions forward, each rooted subtree is
// disjoint from its shifted copy.  Consequently every vertex in that subtree
// leaves it, the upper bound is reached on every edge, and the total is
// globally maximum.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count;
    cin >> node_count;

    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    // Root the tree at 1 only temporarily.  The forward order records parents;
    // reversing it lets us compute all subtree sizes without recursive DFS.
    vector<int> parent(node_count + 1, 0);
    vector<int> subtree_size(node_count + 1, 1);
    vector<int> rooted_order = {1};
    for (size_t index = 0; index < rooted_order.size(); ++index) {
        const int vertex = rooted_order[index];
        for (const int next : graph[vertex]) {
            if (next == parent[vertex]) continue;
            parent[next] = vertex;
            rooted_order.push_back(next);
        }
    }
    for (auto iterator = rooted_order.rbegin(); iterator != rooted_order.rend();
         ++iterator) {
        const int vertex = *iterator;
        if (parent[vertex] != 0) {
            subtree_size[parent[vertex]] += subtree_size[vertex];
        }
    }

    // Removing v creates its child subtrees and the piece above v.  A centroid
    // is a vertex for which the largest of those pieces has size at most N/2.
    int centroid = 1;
    for (const int vertex : rooted_order) {
        int largest_piece = node_count - subtree_size[vertex];
        for (const int next : graph[vertex]) {
            if (parent[next] == vertex) {
                largest_piece = max(largest_piece, subtree_size[next]);
            }
        }
        if (2 * largest_piece <= node_count) {
            centroid = vertex;
            break;
        }
    }

    // Make a genuine DFS preorder rooted at the centroid.  Each rooted subtree
    // is then one contiguous interval, which is the key geometric property of
    // the circular-shift construction.
    vector<int> dfs_parent(node_count + 1, 0);
    vector<int> dfs_order;
    dfs_order.reserve(node_count);
    vector<int> stack = {centroid};
    while (!stack.empty()) {
        const int vertex = stack.back();
        stack.pop_back();
        dfs_order.push_back(vertex);

        // Reverse insertion only makes the result deterministic; either child
        // order preserves the contiguous-subtree property.
        for (auto iterator = graph[vertex].rbegin();
             iterator != graph[vertex].rend(); ++iterator) {
            const int next = *iterator;
            if (next == dfs_parent[vertex]) continue;
            dfs_parent[next] = vertex;
            stack.push_back(next);
        }
    }

    const int shift = node_count / 2;
    vector<int> destination(node_count + 1);
    for (int index = 0; index < node_count; ++index) {
        destination[dfs_order[index]] =
            dfs_order[(index + shift) % node_count];
    }

    // The edge upper bounds add independently.  Subtree sizes may come from
    // any rooting, so reuse the first rooting instead of measuring N paths.
    long long maximum_total_distance = 0;
    for (int vertex = 2; vertex <= node_count; ++vertex) {
        const long long smaller_side =
            min(subtree_size[vertex], node_count - subtree_size[vertex]);
        maximum_total_distance += 2 * smaller_side;
    }

    cout << maximum_total_distance << '\n';
    for (int vertex = 1; vertex <= node_count; ++vertex) {
        if (vertex > 1) cout << ' ';
        cout << destination[vertex];
    }
    cout << '\n';
    return 0;
}
