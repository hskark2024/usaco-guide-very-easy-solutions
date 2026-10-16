#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, edge_count, clone_count;
    cin >> node_count >> edge_count >> clone_count;

    vector<vector<int>> graph(node_count);
    for (int edge = 0; edge < edge_count; ++edge) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    // Build the usual DFS walk without recursion. A frame stores a vertex and
    // the next incident edge to inspect. We record a vertex on entry and the
    // parent again whenever DFS returns from a child.
    vector<char> visited(node_count, false);
    vector<pair<int, size_t>> stack;
    vector<int> walk;
    stack.reserve(node_count);
    walk.reserve(2 * node_count - 1);

    visited[0] = true;
    stack.push_back({0, 0});
    walk.push_back(0);

    while (!stack.empty()) {
        int node = stack.back().first;
        size_t &next_edge = stack.back().second;

        // Skip self-loops, parallel edges to visited nodes, and all edges that
        // are not selected for the DFS spanning tree.
        while (next_edge < graph[node].size() &&
               visited[graph[node][next_edge]]) {
            ++next_edge;
        }

        if (next_edge < graph[node].size()) {
            const int child = graph[node][next_edge++];
            visited[child] = true;
            stack.push_back({child, 0});
            walk.push_back(child);  // Traverse the tree edge down.
        } else {
            stack.pop_back();
            if (!stack.empty()) {
                walk.push_back(stack.back().first);  // Traverse it back up.
            }
        }
    }

    // The DFS walk has at most 2N-1 entries. Consecutive slices therefore
    // cover every vertex while respecting ceil(2N/K) entries per clone.
    const int route_limit = (2 * node_count + clone_count - 1) / clone_count;
    size_t position = 0;
    for (int clone = 0; clone < clone_count; ++clone) {
        if (position == walk.size()) {
            // Every clone must receive a nonempty route. A one-vertex route is
            // always legal and need not contribute a new vertex.
            cout << "1 1\n";
            continue;
        }

        const int route_size = min<int>(route_limit, walk.size() - position);
        cout << route_size;
        for (int index = 0; index < route_size; ++index) {
            cout << ' ' << walk[position++] + 1;
        }
        cout << '\n';
    }

    return 0;
}
