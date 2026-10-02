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

    // Root the tree at vertex 0 and save parents plus preorder.  We avoid a
    // recursive DFS because a 200,000-vertex path could overflow the call
    // stack even though the tree algorithm itself is linear.
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

    // downward[v] is the farthest distance from v to a vertex in v's rooted
    // subtree.  We also remember the two best downward branches at each v.
    // The runner-up is essential: when rerooting into the best child, that
    // child is not allowed to reuse its own branch through the parent.
    vector<int> downward(node_count, 0);
    vector<int> best_branch(node_count, 0);
    vector<int> second_branch(node_count, 0);
    vector<int> best_child(node_count, -1);

    // Reverse preorder puts every child before its parent.
    for (int index = node_count - 1; index >= 0; --index) {
        const int vertex = order[index];
        for (const int child : neighbors[vertex]) {
            if (parent[child] != vertex) {
                continue;
            }

            // Going from vertex into this child's deepest descendant uses
            // one edge plus the best downward path already found at child.
            const int candidate = 1 + downward[child];
            if (candidate > best_branch[vertex]) {
                second_branch[vertex] = best_branch[vertex];
                best_branch[vertex] = candidate;
                best_child[vertex] = child;
            } else if (candidate > second_branch[vertex]) {
                second_branch[vertex] = candidate;
            }
        }
        downward[vertex] = best_branch[vertex];
    }

    // upward[v] is the farthest distance reached by first walking from v to
    // its parent.  Its destination may be the parent itself, somewhere above
    // the parent, or inside a sibling subtree.
    vector<int> upward(node_count, 0);

    // Preorder ensures a parent's upward answer is ready before its children.
    for (const int vertex : order) {
        for (const int child : neighbors[vertex]) {
            if (parent[child] != vertex) {
                continue;
            }

            // Exclude child's own branch.  If child supplied the largest
            // branch, use the runner-up; otherwise the largest remains valid.
            const int sibling_branch =
                (best_child[vertex] == child)
                    ? second_branch[vertex]
                    : best_branch[vertex];

            // The outer +1 crosses child -> vertex.  A zero sibling branch
            // represents stopping at vertex, so leaves work without a special
            // case.  The other option continues through vertex's parent side.
            upward[child] = 1 + max(upward[vertex], sibling_branch);
        }
    }

    // Every path from v either stays in v's subtree or starts with its parent
    // edge, so the larger of the two DP values is exactly the eccentricity.
    for (int vertex = 0; vertex < node_count; ++vertex) {
        if (vertex != 0) {
            cout << ' ';
        }
        cout << max(downward[vertex], upward[vertex]);
    }
    cout << '\n';
    return 0;
}
