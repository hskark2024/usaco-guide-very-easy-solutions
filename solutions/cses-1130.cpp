#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count;
    cin >> node_count;

    vector<vector<int>> neighbors(node_count);
    for (int edge = 0; edge + 1 < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;
        neighbors[first].push_back(second);
        neighbors[second].push_back(first);
    }

    // Build a rooted tree without recursion.  An iterative traversal avoids a
    // stack overflow when the input is one long chain of 200,000 vertices.
    vector<int> parent(node_count, -1);
    vector<int> order;
    order.reserve(node_count);
    parent[0] = 0;
    order.push_back(0);
    for (int index = 0; index < node_count; ++index) {
        const int vertex = order[index];
        for (const int next : neighbors[vertex]) {
            if (next == parent[vertex]) {
                continue;
            }
            parent[next] = vertex;
            order.push_back(next);
        }
    }

    // blocked[v]: best matching in v's subtree when v may not use an edge to
    // a child (because its parent might already match with v).
    // best[v]: best matching when v is free to use at most one child edge.
    vector<int> blocked(node_count, 0);
    vector<int> best(node_count, 0);

    // Children must be solved before their parent, so process reverse order.
    for (int index = node_count - 1; index >= 0; --index) {
        const int vertex = order[index];

        // If vertex uses no child edge, every child is free to take its own
        // best matching independently.
        for (const int child : neighbors[vertex]) {
            if (parent[child] == vertex) {
                blocked[vertex] += best[child];
            }
        }
        best[vertex] = blocked[vertex];

        // Try matching vertex with exactly one child.  That chosen child can
        // no longer match any of its children, while all other child subtrees
        // keep their unrestricted best answers.
        for (const int child : neighbors[vertex]) {
            if (parent[child] != vertex) {
                continue;
            }
            const int candidate = blocked[vertex] - best[child]
                                + blocked[child] + 1;
            best[vertex] = max(best[vertex], candidate);
        }
    }

    cout << best[0] << '\n';
    return 0;
}
