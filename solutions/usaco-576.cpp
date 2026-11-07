#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

// USACO December 2015 Platinum: Max Flow
//
// Each route adds one unit to every vertex on a tree path.  Updating every
// vertex of every route is too slow.  We place four difference markers around
// the route's LCA, then one bottom-up accumulation turns all markers into the
// exact number of routes passing through each vertex.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertex_count, route_count;
    cin >> vertex_count >> route_count;

    vector<vector<int>> graph(vertex_count + 1);
    for (int edge = 1; edge < vertex_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    constexpr int LOG = 18;  // 2^17 > 100,000, so levels 0..17 are enough.
    vector<array<int, LOG>> ancestor(vertex_count + 1);
    vector<int> depth(vertex_count + 1);
    vector<int> order;
    order.reserve(vertex_count);

    // Root the tree at vertex 1.  The growing order vector acts as an explicit
    // DFS/BFS work list and avoids recursive-stack trouble on a long chain.
    order.push_back(1);
    for (size_t index = 0; index < order.size(); ++index) {
        const int vertex = order[index];
        for (int neighbor : graph[vertex]) {
            if (neighbor == ancestor[vertex][0]) {
                continue;
            }
            ancestor[neighbor][0] = vertex;
            depth[neighbor] = depth[vertex] + 1;
            order.push_back(neighbor);
        }
    }

    // Build powers-of-two ancestors after every direct parent is known.
    for (int level = 1; level < LOG; ++level) {
        for (int vertex = 1; vertex <= vertex_count; ++vertex) {
            const int middle = ancestor[vertex][level - 1];
            ancestor[vertex][level] = ancestor[middle][level - 1];
        }
    }

    const auto lowest_common_ancestor = [&](int first, int second) {
        if (depth[first] < depth[second]) {
            swap(first, second);
        }

        // Raise the deeper endpoint until both are on the same level.
        int difference = depth[first] - depth[second];
        for (int level = 0; level < LOG; ++level) {
            if ((difference >> level) & 1) {
                first = ancestor[first][level];
            }
        }
        if (first == second) {
            return first;
        }

        // Jump both endpoints upward whenever the jump keeps them different.
        // After the loop, their direct parent is the first shared ancestor.
        for (int level = LOG - 1; level >= 0; --level) {
            if (ancestor[first][level] != ancestor[second][level]) {
                first = ancestor[first][level];
                second = ancestor[second][level];
            }
        }
        return ancestor[first][0];
    };

    vector<long long> difference(vertex_count + 1);
    for (int route = 0; route < route_count; ++route) {
        int first, second;
        cin >> first >> second;
        const int lca = lowest_common_ancestor(first, second);

        // Endpoint markers begin the two upward path halves.  Removing one at
        // lca and one at parent(lca) makes the inclusive vertex path survive
        // exactly once after child sums flow into their parents.
        ++difference[first];
        ++difference[second];
        --difference[lca];
        --difference[ancestor[lca][0]];
    }

    long long answer = 0;
    // Children appear after parents in order, so reverse order is postorder.
    // Each subtree sum is now complete before it is added to the parent.
    for (auto iterator = order.rbegin(); iterator != order.rend(); ++iterator) {
        const int vertex = *iterator;
        answer = max(answer, difference[vertex]);
        difference[ancestor[vertex][0]] += difference[vertex];
    }

    cout << answer << '\n';
    return 0;
}
