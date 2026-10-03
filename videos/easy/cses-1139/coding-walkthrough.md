# C++ coding walkthrough

1. Read colors and build a zero-based adjacency list.
2. Generate preorder and subtree endpoints with explicit enter/exit events.
3. Allocate one answer per original vertex.
4. Create a Fenwick tree over Euler positions.
5. Reserve an `unordered_map<int, int>` for color representatives.
6. Sweep indices from `N - 1` down to zero.
7. Remove the old representative, mark the current index, and update the map.
8. Query `[entry[v], exit[v])` immediately when the sweep reaches `entry[v]`.
9. Print saved answers in vertex order.
