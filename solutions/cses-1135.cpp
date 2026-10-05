#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, query_count;
    cin >> node_count >> query_count;

    vector<vector<int>> graph(node_count);
    for (int edge = 0; edge + 1 < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    int levels = 1;
    while ((1 << levels) <= node_count) {
        ++levels;
    }

    vector<int> parent(node_count, -1);
    vector<int> depth(node_count, 0);
    vector<int> order;
    order.reserve(node_count);
    order.push_back(0);
    parent[0] = 0;

    // Using a growing vector as a queue avoids recursive DFS.  That matters
    // for a legal tree that is one 200,000-node path.
    for (size_t index = 0; index < order.size(); ++index) {
        int vertex = order[index];
        for (int next : graph[vertex]) {
            if (next == parent[vertex]) {
                continue;
            }
            parent[next] = vertex;
            depth[next] = depth[vertex] + 1;
            order.push_back(next);
        }
    }

    vector<vector<int>> up(levels, vector<int>(node_count));
    up[0] = parent;
    for (int level = 1; level < levels; ++level) {
        for (int vertex = 0; vertex < node_count; ++vertex) {
            int halfway = up[level - 1][vertex];
            up[level][vertex] = up[level - 1][halfway];
        }
    }

    auto lift = [&](int vertex, int steps) {
        for (int level = 0; level < levels; ++level) {
            if ((steps >> level) & 1) {
                vertex = up[level][vertex];
            }
        }
        return vertex;
    };

    auto lowest_common_ancestor = [&](int first, int second) {
        if (depth[first] < depth[second]) {
            swap(first, second);
        }
        first = lift(first, depth[first] - depth[second]);

        if (first == second) {
            return first;
        }

        // A large-to-small greedy scan moves both vertices upward without
        // ever jumping to the same vertex.  Their parents after the scan are
        // exactly the lowest common ancestor.
        for (int level = levels - 1; level >= 0; --level) {
            if (up[level][first] != up[level][second]) {
                first = up[level][first];
                second = up[level][second];
            }
        }
        return up[0][first];
    };

    while (query_count--) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;

        int meeting = lowest_common_ancestor(first, second);

        // The route climbs from each endpoint to the LCA.  Subtracting twice
        // the LCA depth removes the shared root-to-LCA prefix from both depths.
        int distance = depth[first] + depth[second] - 2 * depth[meeting];
        cout << distance << '\n';
    }

    return 0;
}
