#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertex_count;
    int edge_count;
    cin >> vertex_count >> edge_count;

    vector<int> neighbor_mask(vertex_count, 0);
    for (int edge = 0; edge < edge_count; ++edge) {
        int first;
        int second;
        cin >> first >> second;
        --first;
        --second;
        neighbor_mask[first] |= 1 << second;
        neighbor_mask[second] |= 1 << first;
    }

    const int state_count = 1 << vertex_count;

    // is_clique[mask] says whether every pair inside mask has an edge.  Add
    // one least-significant vertex to a smaller known clique; it remains a
    // clique exactly when the new vertex touches everyone already present.
    vector<char> is_clique(state_count, false);
    is_clique[0] = true;
    for (int mask = 1; mask < state_count; ++mask) {
        const int chosen_bit = mask & -mask;
        const int chosen_vertex = __builtin_ctz(chosen_bit);
        const int remainder = mask ^ chosen_bit;
        is_clique[mask] = is_clique[remainder]
            && (neighbor_mask[chosen_vertex] & remainder) == remainder;
    }

    // Removing edges can separate vertices, but it cannot create a missing
    // edge.  Therefore every final connected component must be a clique in
    // the original graph, and the task is exactly minimum clique partition.
    vector<int> minimum_groups(state_count, vertex_count + 1);
    minimum_groups[0] = 0;

    for (int mask = 1; mask < state_count; ++mask) {
        if (is_clique[mask]) {
            minimum_groups[mask] = 1;
            continue;
        }

        // Force the group we peel off to contain one fixed vertex.  Every
        // partition has exactly one group containing that vertex, so this
        // removes symmetric choices without losing an optimal partition.
        const int anchor_bit = mask & -mask;
        const int anchor_vertex = __builtin_ctz(anchor_bit);

        // Vertices not adjacent to the anchor can never share its clique.
        // Removing them before submask enumeration is an important practical
        // speedup for sparse graphs while preserving the O(3^N) worst case.
        const int candidates =
            (mask ^ anchor_bit) & neighbor_mask[anchor_vertex];
        for (int subset = candidates;; subset = (subset - 1) & candidates) {
            const int group = subset | anchor_bit;
            if (is_clique[group]) {
                minimum_groups[mask] = min(
                    minimum_groups[mask],
                    1 + minimum_groups[mask ^ group]
                );
            }
            if (subset == 0) {
                break;
            }
        }
    }

    cout << minimum_groups[state_count - 1] << '\n';
    return 0;
}
