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

    // Root the tree only to organize two iterative passes. The game itself is
    // still undirected; rerooting information will account for the parent side.
    vector<int> parent(node_count, -1);
    vector<int> order;
    order.reserve(node_count);
    order.push_back(0);
    for (size_t index = 0; index < order.size(); ++index) {
        const int node = order[index];
        for (int neighbor : graph[node]) {
            if (neighbor == parent[node]) continue;
            parent[neighbor] = node;
            order.push_back(neighbor);
        }
    }

    // down[node] is the result when the stone has just arrived at node from
    // its parent. Moving back is forbidden because the parent is already active.
    // The state is winning exactly when at least one child is a losing state.
    vector<char> down(node_count, false);
    for (int index = node_count - 1; index >= 0; --index) {
        const int node = order[index];
        for (int neighbor : graph[node]) {
            if (parent[neighbor] == node && !down[neighbor]) {
                down[node] = true;
                break;
            }
        }
    }

    // from_parent[node] is the result of the state at parent[node] after the
    // stone arrived there from node. It summarizes every direction outside
    // node's rooted subtree and is filled in the top-down pass.
    vector<char> from_parent(node_count, true);
    vector<char> starting_state(node_count, false);

    for (int node : order) {
        int losing_moves = 0;

        // Moving from node toward its parent reaches this already-computed
        // outside state. A move is good precisely when the reached state loses.
        if (parent[node] != -1 && !from_parent[node]) ++losing_moves;

        for (int neighbor : graph[node]) {
            if (parent[neighbor] == node && !down[neighbor]) ++losing_moves;
        }

        // Ron wins from this starting node iff he can hand Hermione at least
        // one losing directed state.
        starting_state[node] = (losing_moves > 0);

        for (int child : graph[node]) {
            if (parent[child] != node) continue;

            // When the stone came from this child, that edge is already used.
            // Remove the child's contribution and ask whether any other losing
            // continuation remains at node.
            const int losing_without_child = losing_moves - (!down[child]);
            from_parent[child] = (losing_without_child > 0);
        }
    }

    while (query_count--) {
        int start;
        cin >> start;
        --start;
        cout << (starting_state[start] ? "Ron" : "Hermione") << '\n';
    }

    return 0;
}
