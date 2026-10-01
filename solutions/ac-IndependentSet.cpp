#include <array>
#include <iostream>
#include <vector>

using namespace std;

constexpr long long MOD = 1'000'000'007LL;

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

    // Root the tree iteratively so a chain with 100,000 nodes is safe.
    vector<int> parent(node_count, -1);
    vector<int> order{0};
    order.reserve(node_count);
    parent[0] = 0;
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

    // ways[v][0] counts valid colorings of v's subtree when v is white.
    // ways[v][1] counts them when v is black.
    vector<array<long long, 2>> ways(node_count, {1, 1});

    for (int index = node_count - 1; index >= 0; --index) {
        const int vertex = order[index];
        for (const int child : neighbors[vertex]) {
            if (parent[child] != vertex) {
                continue;
            }

            // A white parent accepts either child color.
            const long long any_child_color =
                (ways[child][0] + ways[child][1]) % MOD;
            ways[vertex][0] = ways[vertex][0] * any_child_color % MOD;

            // A black parent forces every child to be white.
            ways[vertex][1] = ways[vertex][1] * ways[child][0] % MOD;
        }
    }

    cout << (ways[0][0] + ways[0][1]) % MOD << '\n';
    return 0;
}
