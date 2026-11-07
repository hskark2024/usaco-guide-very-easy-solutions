#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Codeforces Gym 102694C: Sloth Naptime
//
// Every query asks for the vertex reached after walking at most "energy" edges
// along the unique path from start to finish.  The path first climbs from start
// to the LCA and then descends toward finish.  Binary lifting lets us locate a
// vertex on either half in O(log N) time.
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

    int log = 1;
    while ((1 << log) <= node_count) ++log;

    vector<int> parent(node_count + 1), depth(node_count + 1);
    vector<int> order = {1};
    parent[1] = 1;

    // An iterative traversal avoids overflowing the call stack on a chain of
    // 300,000 vertices.  A parent is fixed before its children are appended.
    for (size_t index = 0; index < order.size(); ++index) {
        const int vertex = order[index];
        for (const int next : graph[vertex]) {
            if (next == parent[vertex]) continue;
            parent[next] = vertex;
            depth[next] = depth[vertex] + 1;
            order.push_back(next);
        }
    }

    // up[level][v] is the ancestor 2^level edges above v.  The root points to
    // itself, which keeps every table lookup inside the valid vertex range.
    vector<vector<int>> up(log, vector<int>(node_count + 1));
    up[0] = parent;
    for (int level = 1; level < log; ++level) {
        for (int vertex = 1; vertex <= node_count; ++vertex) {
            up[level][vertex] = up[level - 1][up[level - 1][vertex]];
        }
    }

    const auto climb = [&](int vertex, int distance) {
        for (int level = 0; level < log; ++level) {
            if ((distance >> level) & 1) vertex = up[level][vertex];
        }
        return vertex;
    };

    const auto lca = [&](int first, int second) {
        if (depth[first] < depth[second]) swap(first, second);
        first = climb(first, depth[first] - depth[second]);
        if (first == second) return first;

        // Move both vertices upward without jumping over their first common
        // ancestor.  After the loop, their parents are exactly the LCA.
        for (int level = log - 1; level >= 0; --level) {
            if (up[level][first] != up[level][second]) {
                first = up[level][first];
                second = up[level][second];
            }
        }
        return parent[first];
    };

    int query_count;
    cin >> query_count;
    while (query_count--) {
        int start, finish, energy;
        cin >> start >> finish >> energy;

        const int meeting = lca(start, finish);
        const int upward_length = depth[start] - depth[meeting];
        const int downward_length = depth[finish] - depth[meeting];
        const int path_length = upward_length + downward_length;

        if (energy >= path_length) {
            // The sloth cannot walk beyond its destination.
            cout << finish << '\n';
        } else if (energy <= upward_length) {
            // This point lies on the start-to-LCA half.
            cout << climb(start, energy) << '\n';
        } else {
            // The desired point lies on the downward half.  Climbing from the
            // finish by the unwalked suffix reaches the same point directly.
            const int unwalked_suffix = path_length - energy;
            cout << climb(finish, unwalked_suffix) << '\n';
        }
    }
    return 0;
}
